#include "plugin.h"

#include <QApplication>
#include <QHeaderView>
#include <QInputDialog>
#include <QKeyEvent>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QScrollBar>
#include <QSignalBlocker>
#include <QStringList>
#include <QStyledItemDelegate>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

namespace {

enum RuleRoles { RuleIndexRole = Qt::UserRole, RuleActiveRole = Qt::UserRole + 1 };
class StatusDotDelegate final : public QStyledItemDelegate {
  public:
    explicit StatusDotDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override {
        QStyleOptionViewItem opt(option);
        initStyleOption(&opt, index);

        /*
         * The Active column doesn't contain text.
         */
        if (index.column() == 0) {
            opt.text.clear();
            opt.icon = QIcon();
        }

        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

        painter->save();

        /*
         * Active status dot.
         */
        if (index.column() == 0) {
            const bool active = index.data(RuleActiveRole).toBool();

            constexpr int diameter = 10;

            const QColor dotColor = active ? QColor(0x4c, 0xaf, 0x50) : QColor(0xd9, 0x53, 0x4f);

            const QPoint center = option.rect.center();

            const QRectF dotRect(center.x() - diameter / 2.0, center.y() - diameter / 2.0, diameter,
                                 diameter);

            painter->setRenderHint(QPainter::Antialiasing, true);

            painter->setPen(Qt::NoPen);
            painter->setBrush(dotColor);

            painter->drawEllipse(dotRect);
        }

        painter->restore();
    }
};

class CapabilityTable final : public QTableWidget {
  public:
    explicit CapabilityTable(QWidget* parent = nullptr) : QTableWidget(parent) {}

    std::function<void()> onInsert;
    std::function<void()> onDelete;
    std::function<void()> onEnter;
    std::function<void(int)> onMove;

  protected:
    void keyPressEvent(QKeyEvent* event) override {
        switch (event->key()) {
        case Qt::Key_Insert:
            if (onInsert)
                onInsert();
            event->accept();
            return;

        case Qt::Key_Delete:
            if (onDelete)
                onDelete();
            event->accept();
            return;

        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (onEnter)
                onEnter();
            event->accept();
            return;

        case Qt::Key_Up:
            if (onMove)
                onMove(-1);
            event->accept();
            return;

        case Qt::Key_Down:
            if (onMove)
                onMove(1);
            event->accept();
            return;

        default:
            QTableWidget::keyPressEvent(event);
            return;
        }
    }
};

class CapabilityView final : public QWidget {
  public:
    explicit CapabilityView(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Capabilities");

        setupUi();

        auto* timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [this]() { refresh(); });

        timer->start(250);

        refresh();
    }

    void refresh() {
        if (!table)
            return;

        /*
         * Remember the currently selected logical rule.
         */
        int selectedIndex = -1;

        const QModelIndexList selectedIndexes = table->selectionModel()->selectedRows();

        if (!selectedIndexes.isEmpty()) {
            const int row = selectedIndexes.first().row();

            if (auto* item = table->item(row, 1)) {
                selectedIndex = item->data(RuleIndexRole).toInt();
            }
        }

        const int scrollValue = table->verticalScrollBar()->value();

        /*
         * Current valid rules.
         */
        std::vector<size_t> currentRuleIndices;

        for (size_t i = 0; i < rules.size(); ++i) {
            if (rules[i])
                currentRuleIndices.push_back(i);
        }

        /*
         * Check whether the rule set itself changed.
         *
         * We compare sorted index lists so that changing the visual
         * sort order does not cause a table rebuild.
         */
        std::vector<size_t> knownRuleIndices = lastRuleIndices;

        std::sort(currentRuleIndices.begin(), currentRuleIndices.end());

        std::sort(knownRuleIndices.begin(), knownRuleIndices.end());

        const bool structureChanged = currentRuleIndices != knownRuleIndices;

        /*
         * We don't want to rebuild the table every 250 ms.
         */
        QSignalBlocker blocker(table);

        table->setSortingEnabled(false);

        bool nameChanged = false;

        if (structureChanged) {
            table->setRowCount(0);

            /*
             * Rebuild in rules[] order.
             */
            for (size_t i = 0; i < rules.size(); ++i) {
                if (!rules[i])
                    continue;

                addRow(static_cast<int>(i));
            }

            /*
             * Save the logical structure, not the visual order.
             */
            lastRuleIndices.clear();

            for (size_t i = 0; i < rules.size(); ++i) {
                if (rules[i])
                    lastRuleIndices.push_back(i);
            }
        } else {
            /*
             * Update existing rows in-place.
             *
             * The RuleIndexRole tells us which rule each visual row
             * currently represents, regardless of sorting.
             */
            for (int row = 0; row < table->rowCount(); ++row) {
                auto* item = table->item(row, 1);

                if (!item)
                    continue;

                const int ruleIndex = item->data(RuleIndexRole).toInt();

                if (updateRow(row, ruleIndex)) {
                    nameChanged = true;
                }
            }
        }

        /*
         * Only sort when we actually rebuilt the table or a rule name
         * changed.
         */
        if (structureChanged || nameChanged) {
            table->sortItems(1, nameSortOrder);

            table->horizontalHeader()->setSortIndicator(1, nameSortOrder);
        }

        /*
         * A rebuild or a name change can change the row location,
         * so restore the selected logical rule.
         *
         * For ordinary TID updates, we leave selection completely alone.
         */
        if (structureChanged || nameChanged) {
            if (selectedIndex != -1) {
                for (int row = 0; row < table->rowCount(); ++row) {
                    auto* item = table->item(row, 1);

                    if (!item)
                        continue;

                    if (item->data(RuleIndexRole).toInt() == selectedIndex) {
                        table->selectRow(row);
                        break;
                    }
                }
            }

            table->verticalScrollBar()->setValue(scrollValue);
        }
    }

  private:
    CapabilityTable* table = nullptr;

    /*
     * Logical rule indices currently represented by the table.
     */
    std::vector<size_t> lastRuleIndices;

    /*
     * Only Name uses sorting.
     *
     * Clicking Name:
     *     first  -> ascending
     *     second -> descending
     *     third  -> ascending
     *     ...
     */
    Qt::SortOrder nameSortOrder = Qt::AscendingOrder;

    void addRow(int ruleIndex) {
        if (ruleIndex < 0 || ruleIndex >= static_cast<int>(rules.size()) || !rules[ruleIndex]) {
            return;
        }

        const auto& rule = rules[ruleIndex];

        const int row = table->rowCount();

        table->insertRow(row);

        /*
         * Active
         */
        auto* activeItem = new QTableWidgetItem();

        activeItem->setData(RuleIndexRole, ruleIndex);

        activeItem->setData(RuleActiveRole, rule->getActive());

        activeItem->setToolTip(rule->getActive() ? "Active" : "Inactive");

        table->setItem(row, 0, activeItem);

        /*
         * Name
         */
        const QString name = QString::fromStdString(rule->getName());

        auto* nameItem = new QTableWidgetItem(name);

        nameItem->setData(RuleIndexRole, ruleIndex);

        nameItem->setToolTip(name);

        table->setItem(row, 1, nameItem);

        /*
         * Matches by TID
         */
        QStringList matches;

        for (int tid : rule->getMatchingThreads()) {
            matches << QString::number(tid);
        }

        const QString matchText = matches.isEmpty() ? "No matches yet." : matches.join(", ");

        auto* matchesItem = new QTableWidgetItem(matchText);

        matchesItem->setData(RuleIndexRole, ruleIndex);

        matchesItem->setToolTip(matchText);

        table->setItem(row, 2, matchesItem);

        /*
         * Expression
         */
        const QString expression = QString::fromStdString(rule->getExpression());

        auto* expressionItem = new QTableWidgetItem(expression);

        expressionItem->setData(RuleIndexRole, ruleIndex);

        expressionItem->setToolTip(expression);

        table->setItem(row, 3, expressionItem);
    }

    /*
     * Returns true when the Name changed.
     */
    bool updateRow(int row, int ruleIndex) {
        if (ruleIndex < 0 || ruleIndex >= static_cast<int>(rules.size()) || !rules[ruleIndex]) {
            return false;
        }

        const auto& rule = rules[ruleIndex];

        /*
         * Active
         */
        if (auto* item = table->item(row, 0)) {
            item->setData(RuleIndexRole, ruleIndex);

            item->setData(RuleActiveRole, rule->getActive());

            item->setToolTip(rule->getActive() ? "Active" : "Inactive");
        }

        /*
         * Name
         */
        bool nameChanged = false;

        if (auto* item = table->item(row, 1)) {
            const QString name = QString::fromStdString(rule->getName());

            if (item->text() != name) {
                item->setText(name);
                nameChanged = true;
            }

            item->setData(RuleIndexRole, ruleIndex);

            item->setToolTip(name);
        }

        /*
         * Matches by TID
         */
        QStringList matches;

        for (int tid : rule->getMatchingThreads()) {
            matches << QString::number(tid);
        }

        const QString matchText = matches.isEmpty() ? "No matches yet" : matches.join(", ");

        if (auto* item = table->item(row, 2)) {
            if (item->text() != matchText)
                item->setText(matchText);

            item->setData(RuleIndexRole, ruleIndex);

            item->setToolTip(matchText);
        }

        /*
         * Expression
         */
        if (auto* item = table->item(row, 3)) {
            const QString expression = QString::fromStdString(rule->getExpression());

            if (item->text() != expression)
                item->setText(expression);

            item->setData(RuleIndexRole, ruleIndex);

            item->setToolTip(expression);
        }

        return nameChanged;
    }

    void setupUi() {
        auto* layout = new QVBoxLayout(this);

        layout->setContentsMargins(0, 0, 0, 0);

        layout->setSpacing(0);

        table = new CapabilityTable(this);

        table->onInsert = [this]() { addRule(); };

        table->onDelete = [this]() {
            const QModelIndexList selected = table->selectionModel()->selectedRows();

            if (selected.isEmpty())
                return;

            const int row = selected.first().row();

            auto* item = table->item(row, 1);

            if (!item)
                return;

            const int index = item->data(RuleIndexRole).toInt();

            deleteRule(index);
        };

        table->onEnter = [this]() {
            const QModelIndexList selected = table->selectionModel()->selectedRows();

            if (selected.isEmpty())
                return;

            renameRule(selected.first().row());
        };

        table->onMove = [this](int direction) { moveSelection(direction); };

        table->installEventFilter(this);

        table->setColumnCount(4);

        table->setHorizontalHeaderLabels({"Active", "Name", "Matches by TID", "Expression"});

        /*
         * We handle sorting ourselves so that only Name is sortable.
         */
        table->setSortingEnabled(false);

        table->setFont(QApplication::font());

        table->setShowGrid(true);
        table->setGridStyle(Qt::SolidLine);
        table->setStyleSheet("QTableWidget {"
                             "    gridline-color: #717171;"
                             "}"
                             "QTableWidget::item {"
                             "    padding-left: 5px;"
                             "}"
                             "QHeaderView::section {"
                             "    padding-left: 5px;"
                             "    border-right: 1px solid #717171;"
                             "    border-bottom: 1px solid #717171;"
                             "}");

        table->setWordWrap(false);

        table->setTextElideMode(Qt::ElideRight);

        table->setSelectionBehavior(QAbstractItemView::SelectRows);

        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table->verticalHeader()->hide();

        table->verticalHeader()->setDefaultSectionSize(QFontMetrics(table->font()).height() + 2);

        QHeaderView* header = table->horizontalHeader();

        header->setHighlightSections(false);

        header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        /*
         * -------------------------------------------------------------
         * Active
         * -------------------------------------------------------------
         *
         * Slightly wider than before: this creates a small amount of
         * breathing room between Active and Name.
         */
        header->setSectionResizeMode(0, QHeaderView::Fixed);

        table->setColumnWidth(0, 44);

        /*
         * -------------------------------------------------------------
         * Name
         * -------------------------------------------------------------
         */
        header->setSectionResizeMode(1, QHeaderView::Interactive);

        table->setColumnWidth(1, 220);

        /*
         * -------------------------------------------------------------
         * Matches by TID
         * -------------------------------------------------------------
         */
        header->setSectionResizeMode(2, QHeaderView::Interactive);

        table->setColumnWidth(2, 150);

        /*
         * -------------------------------------------------------------
         * Expression
         * -------------------------------------------------------------
         */
        header->setSectionResizeMode(3, QHeaderView::Stretch);

        header->setStretchLastSection(false);

        /*
         * Show the sort arrow on Name.
         */
        header->setSortIndicatorShown(true);

        header->setSortIndicator(1, nameSortOrder);

        /*
         * Status dot.
         */
        table->setItemDelegate(new StatusDotDelegate(table));

        layout->addWidget(table);

        /*
         * -------------------------------------------------------------
         * Active click
         * -------------------------------------------------------------
         */
        connect(table, &QTableWidget::cellClicked, this, [this](int row, int column) {
            if (column != 0)
                return;

            auto* item = table->item(row, 0);

            if (!item)
                return;

            const int index = item->data(RuleIndexRole).toInt();

            if (index < 0 || index >= static_cast<int>(rules.size()) || !rules[index]) {
                return;
            }

            const bool active = !rules[index]->getActive();

            rules[index]->setActive(active);

            item->setData(RuleActiveRole, active);

            item->setToolTip(active ? "Active" : "Inactive");

            table->viewport()->update(table->visualItemRect(item));
        });

        /*
         * -------------------------------------------------------------
         * Name double-click
         * -------------------------------------------------------------
         */
        connect(table, &QTableWidget::cellDoubleClicked, this, [this](int row, int column) {
            if (column == 1)
                renameRule(row);
        });

        /*
         * -------------------------------------------------------------
         * Name sorting
         * -------------------------------------------------------------
         *
         * Only section 1 responds.
         *
         * First click:
         *     ascending
         *
         * Second click:
         *     descending
         *
         * The arrow is displayed by QHeaderView.
         */
        connect(header, &QHeaderView::sectionClicked, this, [this, header](int section) {
            if (section != 1)
                return;

            if (nameSortOrder == Qt::AscendingOrder) {
                nameSortOrder = Qt::DescendingOrder;
            } else {
                nameSortOrder = Qt::AscendingOrder;
            }

            header->setSortIndicator(1, nameSortOrder);

            table->sortItems(1, nameSortOrder);
        });

        /*
         * Empty-space click deselects everything.
         */
        table->viewport()->installEventFilter(this);

        /*
         * Context menu.
         */
        table->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(table, &QTableWidget::customContextMenuRequested, this,
                [this](const QPoint& pos) { showContextMenu(pos); });
    }

    bool eventFilter(QObject* watched, QEvent* event) override {
        if (watched == table->viewport() && event->type() == QEvent::MouseButtonPress) {
            auto* mouseEvent = static_cast<QMouseEvent*>(event);

            if (mouseEvent->button() == Qt::LeftButton) {
                const QPoint pos = mouseEvent->localPos().toPoint();

                if (!table->itemAt(pos)) {
                    table->clearSelection();
                    return true;
                }
            }
        }

        return QWidget::eventFilter(watched, event);
    }

    void moveSelection(int direction) {
        const int rowCount = table->rowCount();

        if (rowCount == 0)
            return;

        int currentRow = -1;

        const QModelIndexList selected = table->selectionModel()->selectedRows();

        if (!selected.isEmpty())
            currentRow = selected.first().row();

        int newRow;

        if (currentRow == -1) {
            /*
             * No selection:
             * Down selects first, Up selects last.
             */
            newRow = direction > 0 ? 0 : rowCount - 1;
        } else {
            newRow = currentRow + direction;

            /*
             * Don't wrap around.
             */
            if (newRow < 0)
                newRow = 0;

            if (newRow >= rowCount)
                newRow = rowCount - 1;
        }

        table->setCurrentCell(newRow, 1);

        table->selectionModel()->select(table->model()->index(newRow, 0),
                                        QItemSelectionModel::ClearAndSelect |
                                            QItemSelectionModel::Rows);

        table->scrollToItem(table->item(newRow, 1), QAbstractItemView::PositionAtCenter);
    }

    void renameRule(int row) {
        auto* item = table->item(row, 1);

        if (!item)
            return;

        const int index = item->data(RuleIndexRole).toInt();

        if (index < 0 || index >= static_cast<int>(rules.size()) || !rules[index]) {
            return;
        }

        bool ok = false;

        const QString oldName = QString::fromStdString(rules[index]->getName());

        QString newName =
            QInputDialog::getText(this, "Rename Rule", "Name:", QLineEdit::Normal, oldName, &ok);

        if (!ok)
            return;

        newName = newName.trimmed();

        if (newName.isEmpty())
            return;

        rules[index]->setName(newName.toStdString());

        item->setText(newName);
        item->setToolTip(newName);

        /*
         * Re-apply the current Name sorting immediately.
         */
        table->sortItems(1, nameSortOrder);

        table->horizontalHeader()->setSortIndicator(1, nameSortOrder);
    }

    void showContextMenu(const QPoint& pos) {
        const int row = table->rowAt(pos.y());

        QMenu menu(this);

        if (row < 0) {
            menu.addAction("Add rule", [this]() { addRule(); });
        } else {
            auto* item = table->item(row, 1);

            if (!item)
                return;

            const int index = item->data(RuleIndexRole).toInt();

            if (index < 0 || index >= static_cast<int>(rules.size()) || !rules[index]) {
                return;
            }

            menu.addAction("Rename", [this, row]() { renameRule(row); });

            menu.addAction(rules[index]->getActive() ? "Deactivate" : "Activate", [this, index]() {
                rules[index]->setActive(!rules[index]->getActive());

                refresh();
            });

            menu.addSeparator();

            menu.addAction("Delete", [this, index]() { deleteRule(index); });
        }

        menu.exec(table->viewport()->mapToGlobal(pos));
    }

    void addRule() {
        bool ok = false;

        QString name = QInputDialog::getText(this, "Add Rule", "Name:", QLineEdit::Normal, "", &ok);

        if (!ok || name.trimmed().isEmpty()) {
            return;
        }

        QString expression =
            QInputDialog::getText(this, "Add Rule", "Expression:", QLineEdit::Normal, "", &ok);

        if (!ok || expression.trimmed().isEmpty()) {
            return;
        }

        try {
            ::addRule(name.trimmed().toStdString(), expression.trimmed().toStdString());

            /*
             * Force table reconstruction.
             */
            lastRuleIndices.clear();

            refresh();
        } catch (const std::exception& e) {
            _plugin_logprintf("Failed to add rule: %s\n", e.what());
        }
    }

    void deleteRule(int index) {
        if (index < 0 || index >= static_cast<int>(rules.size())) {
            return;
        }

        /*
         * Find the visual row corresponding to this logical rules[] index.
         */
        int rowToRemove = -1;

        for (int row = 0; row < table->rowCount(); ++row) {
            auto* item = table->item(row, 1);

            if (!item)
                continue;

            if (item->data(RuleIndexRole).toInt() == index) {
                rowToRemove = row;
                break;
            }
        }

        /*
         * Remove the rule and its hook nodes.
         */
        removeRule(static_cast<size_t>(index));

        /*
         * Remove the row immediately from the Qt table.
         */
        if (rowToRemove != -1)
            table->removeRow(rowToRemove);

        /*
         * rules[] indices after the deleted rule have shifted down by one.
         * Update RuleIndexRole for the remaining rows.
         */
        for (int row = 0; row < table->rowCount(); ++row) {
            for (int column = 0; column < table->columnCount(); ++column) {
                auto* item = table->item(row, column);

                if (!item)
                    continue;

                const int oldIndex = item->data(RuleIndexRole).toInt();

                if (oldIndex > index) {
                    item->setData(RuleIndexRole, oldIndex - 1);
                }
            }
        }

        /*
         * Keep our cached logical rule list in sync.
         */
        lastRuleIndices.clear();

        for (size_t i = 0; i < rules.size(); ++i) {
            if (rules[i])
                lastRuleIndices.push_back(i);
        }
    }
};

} // namespace

static CapabilityView* capabilityView = nullptr;

void CreateCapabilityView() {
    if (capabilityView)
        return;

    capabilityView = new CapabilityView();

    GuiAddQWidgetTab(capabilityView);
}

void DestroyCapabilityView() {
    if (!capabilityView)
        return;

    CapabilityView* view = capabilityView;
    capabilityView = nullptr;

    GuiCloseQWidgetTab(view);
    view->close();
    delete view;
}

void RefreshCapabilityView() {
    if (!capabilityView)
        return;

    capabilityView->refresh();
}