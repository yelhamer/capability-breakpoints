#include "plugin.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QFontDatabase>
#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QInputDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMetaObject>
#include <QMouseEvent>
#include <QMutex>
#include <QMutexLocker>
#include <QPainter>
#include <QPalette>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QSignalBlocker>
#include <QSplitter>
#include <QStringList>
#include <QStyle>
#include <QStyledItemDelegate>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextOption>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

static QString capabilityStyleSheet() {
    return R"(
        QWidget {
            background-color: #1e1f22;
            color: #d7d9dc;
            font-family: "Segoe UI";
            font-size: 9pt;
        }

        QDialog {
            background-color: #1e1f22;
        }

        QLabel {
            color: #d7d9dc;
        }

        QLabel[class="title"] {
            color: #ffffff;
            font-size: 13pt;
            font-weight: 600;
        }

        QLabel[class="subtitle"] {
            color: #8f949b;
            font-size: 8pt;
        }

        QLabel[class="section"] {
            color: #ffffff;
            font-size: 9pt;
            font-weight: 600;
            padding-top: 4px;
            padding-bottom: 3px;
        }

        QTableWidget {
            background-color: #191a1d;
            alternate-background-color: #1d1f22;
            border: 1px solid #34363b;
            border-radius: 4px;
            gridline-color: #2c2e33;
            selection-background-color: #294b6b;
            selection-color: #ffffff;
            outline: none;
        }

        QTableWidget::item {
            padding: 5px 7px;
            border: none;
        }

        QTableWidget::item:selected {
            background-color: #294b6b;
            color: #ffffff;
        }

        QHeaderView {
            background-color: #25272b;
        }

        QHeaderView::section {
            background-color: #25272b;
            color: #aeb3ba;
            border: none;
            border-right: 1px solid #34363b;
            border-bottom: 1px solid #3a3c42;
            padding: 6px 8px;
            font-weight: 600;
        }

        QHeaderView::section:hover {
            background-color: #2d3035;
            color: #ffffff;
        }

        QScrollBar:vertical {
            background: #191a1d;
            width: 11px;
            margin: 0;
        }

        QScrollBar::handle:vertical {
            background: #45484f;
            min-height: 25px;
            border-radius: 5px;
            margin: 2px;
        }

        QScrollBar::handle:vertical:hover {
            background: #5a5e66;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }

        QScrollBar:horizontal {
            background: #191a1d;
            height: 11px;
        }

        QScrollBar::handle:horizontal {
            background: #45484f;
            min-width: 25px;
            border-radius: 5px;
            margin: 2px;
        }

        QPlainTextEdit {
            background-color: #17181b;
            color: #cdd1d6;
            border: 1px solid #34363b;
            border-radius: 4px;
            padding: 6px;
            selection-background-color: #294b6b;
            font-family: "Cascadia Mono", "Consolas", monospace;
            font-size: 9pt;
        }

        QComboBox {
            background-color: #292b30;
            color: #d7d9dc;
            border: 1px solid #3d4046;
            border-radius: 4px;
            padding: 5px 8px;
            min-height: 18px;
        }

        QComboBox:hover {
            border-color: #557da5;
        }

        QComboBox::drop-down {
            border: none;
            width: 24px;
        }

        QComboBox QAbstractItemView {
            background-color: #25272b;
            color: #d7d9dc;
            border: 1px solid #45484f;
            selection-background-color: #294b6b;
        }

        QLineEdit {
            background-color: #17181b;
            color: #ffffff;
            border: 1px solid #3d4046;
            border-radius: 4px;
            padding: 5px 7px;
        }

        QLineEdit:focus {
            border-color: #557da5;
        }

        QGroupBox {
            border: 1px solid #34363b;
            border-radius: 5px;
            margin-top: 10px;
            padding: 10px 8px 8px 8px;
            color: #aeb3ba;
            font-weight: 600;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
            color: #aeb3ba;
            background-color: #1e1f22;
        }

        QSplitter::handle {
            background-color: #34363b;
        }

        QSplitter::handle:hover {
            background-color: #4c5663;
        }

        QMenu {
            background-color: #25272b;
            color: #d7d9dc;
            border: 1px solid #45484f;
            padding: 4px;
        }

        QMenu::item {
            padding: 6px 28px 6px 10px;
            border-radius: 3px;
        }

        QMenu::item:selected {
            background-color: #294b6b;
        }

        QPushButton {
            background-color: #292b30;
            color: #d7d9dc;
            border: 1px solid #3d4046;
            border-radius: 4px;
            padding: 5px 12px;
        }

        QPushButton:hover {
            background-color: #34373d;
            border-color: #557da5;
        }

        QPushButton:pressed {
            background-color: #202226;
        }
    )";
}

static QMutex matchMutex;
static std::vector<std::shared_ptr<Match>> pendingMatches;

void ProcessPendingMatches();

namespace {

QString formatAddress(duint address) {
    return QString("0x%1").arg(static_cast<qulonglong>(address), sizeof(duint) * 2, 16, QChar('0'));
}

QString formatBytes(const std::vector<std::byte>& bytes) {
    if (bytes.empty())
        return QString();

    QString text;

    for (size_t i = 0; i < bytes.size(); ++i) {
        text += QString("%1").arg(static_cast<unsigned int>(bytes[i]), 2, 16, QChar('0'));

        if (i + 1 < bytes.size())
            text += ' ';
    }

    return text;
}

/*
 * ------------------------------------------------------------
 * Rule match detail window
 * ------------------------------------------------------------
 */
class RuleMatchDialog final : public QDialog {
  public:
    explicit RuleMatchDialog(std::shared_ptr<Match> match, QWidget* parent = nullptr)
        : QDialog(parent), match(std::move(match)) {
        setupUi();
        populate();
    }

  private:
    std::shared_ptr<Match> match;

    QTableWidget* apiTable = nullptr;

    QComboBox* stateSelector = nullptr;

    QPlainTextEdit* argumentsView = nullptr;
    QPlainTextEdit* stackView = nullptr;

    std::vector<Nodes::ApiNodePtr> orderedApiNodes;

    void setupUi() {
        Rule* rule = match->getRule();

        if (!rule)
            return;

        setWindowTitle(QString("Rule Match — %1").arg(QString::fromStdString(rule->getName())));

        resize(820, 600);
        setMinimumSize(700, 500);

        setStyleSheet(capabilityStyleSheet());

        auto* layout = new QVBoxLayout(this);
        layout->setContentsMargins(14, 14, 14, 14);
        layout->setSpacing(10);

        /*
         * ------------------------------------------------------------
         * Header
         * ------------------------------------------------------------
         */

        auto* header = new QWidget(this);

        auto* headerLayout = new QHBoxLayout(header);
        headerLayout->setContentsMargins(0, 0, 0, 0);
        headerLayout->setSpacing(10);

        auto* title = new QLabel(header);

        title->setProperty("class", "title");

        title->setText(QString::fromStdString(rule->getName()));

        headerLayout->addWidget(title);

        headerLayout->addStretch();

        auto* tid = new QLabel(header);

        tid->setProperty("class", "subtitle");

        tid->setText(QString("TID %1").arg(match->getThreadId()));

        headerLayout->addWidget(tid);

        layout->addWidget(header);

        /*
         * ------------------------------------------------------------
         * Expression
         * ------------------------------------------------------------
         */

        auto* expressionBox = new QGroupBox("Expression", this);

        auto* expressionLayout = new QVBoxLayout(expressionBox);

        expressionLayout->setContentsMargins(10, 8, 10, 10);

        auto* expression = new QLineEdit(expressionBox);

        expression->setReadOnly(true);

        expression->setText(QString::fromStdString(rule->getExpression()));

        expressionLayout->addWidget(expression);

        layout->addWidget(expressionBox);

        /*
         * ------------------------------------------------------------
         * API trace
         * ------------------------------------------------------------
         */

        auto* apiBox = new QGroupBox("API Trace", this);

        auto* apiLayout = new QVBoxLayout(apiBox);

        apiLayout->setContentsMargins(8, 8, 8, 8);

        apiTable = new QTableWidget(apiBox);

        apiTable->setColumnCount(2);

        apiTable->setHorizontalHeaderLabels({"Immediate Caller", "API"});

        apiTable->setSelectionBehavior(QAbstractItemView::SelectRows);

        apiTable->setSelectionMode(QAbstractItemView::SingleSelection);

        apiTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

        apiTable->setFocusPolicy(Qt::StrongFocus);

        apiTable->setWordWrap(false);

        apiTable->verticalHeader()->hide();

        apiTable->verticalHeader()->setDefaultSectionSize(28);

        apiTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

        apiTable->setColumnWidth(0, 190);

        apiTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

        apiLayout->addWidget(apiTable);

        layout->addWidget(apiBox, 3);

        /*
         * ------------------------------------------------------------
         * Extended context
         * ------------------------------------------------------------
         */

        auto* contextBox = new QGroupBox("Extended Context", this);

        auto* contextLayout = new QVBoxLayout(contextBox);

        contextLayout->setContentsMargins(8, 8, 8, 8);
        contextLayout->setSpacing(7);

        /*
         * Observation selector
         */

        auto* stateLayout = new QHBoxLayout();

        auto* stateLabel = new QLabel("Observation:", contextBox);

        stateSelector = new QComboBox(contextBox);

        stateSelector->setMinimumWidth(260);

        stateLayout->addWidget(stateLabel);

        stateLayout->addWidget(stateSelector);

        stateLayout->addStretch();

        contextLayout->addLayout(stateLayout);

        /*
         * Arguments + stack
         */

        auto* splitter = new QSplitter(Qt::Horizontal, contextBox);

        /*
         * Arguments
         */

        auto* argumentsWidget = new QWidget(splitter);

        auto* argumentsLayout = new QVBoxLayout(argumentsWidget);

        argumentsLayout->setContentsMargins(0, 0, 4, 0);

        auto* argumentsTitle = new QLabel("Arguments", argumentsWidget);

        argumentsTitle->setProperty("class", "section");

        argumentsView = new QPlainTextEdit(argumentsWidget);

        argumentsView->setReadOnly(true);

        argumentsView->setLineWrapMode(QPlainTextEdit::NoWrap);

        argumentsLayout->addWidget(argumentsTitle);
        argumentsLayout->addWidget(argumentsView);

        /*
         * Stack
         */

        auto* stackWidget = new QWidget(splitter);

        auto* stackLayout = new QVBoxLayout(stackWidget);

        stackLayout->setContentsMargins(4, 0, 0, 0);

        auto* stackTitle = new QLabel("Call Stack", stackWidget);

        stackTitle->setProperty("class", "section");

        stackView = new QPlainTextEdit(stackWidget);

        stackView->setReadOnly(true);

        stackView->setLineWrapMode(QPlainTextEdit::NoWrap);

        stackLayout->addWidget(stackTitle);
        stackLayout->addWidget(stackView);

        splitter->addWidget(argumentsWidget);
        splitter->addWidget(stackWidget);

        splitter->setSizes({350, 600});

        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 2);

        contextLayout->addWidget(splitter, 1);

        layout->addWidget(contextBox, 4);

        /*
         * ------------------------------------------------------------
         * Selection handling
         * ------------------------------------------------------------
         */

        connect(apiTable, &QTableWidget::currentCellChanged, this,
                [this](int currentRow, int, int, int) {
                    if (currentRow < 0 || currentRow >= static_cast<int>(orderedApiNodes.size())) {

                        stateSelector->clear();
                        argumentsView->clear();
                        stackView->clear();

                        return;
                    }

                    populateStates(orderedApiNodes[currentRow]);
                });

        connect(stateSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
                [this](int index) { showState(index); });
    }

    void populate() {
        Rule* rule = match->getRule();

        if (!rule)
            return;

        auto nodes = rule->getOrderedApiCallNodes();

        if (!nodes)
            return;

        orderedApiNodes = *nodes;

        apiTable->setRowCount(0);

        for (const auto& node : orderedApiNodes) {
            if (!node)
                continue;

            const int row = apiTable->rowCount();

            apiTable->insertRow(row);

            /*
             * API
             */
            auto* apiItem = new QTableWidgetItem(QString::fromStdString(node->getApiName()));

            apiTable->setItem(row, 1, apiItem);

            /*
             * States recorded for this exact node.
             */
            StatePtrList states = match->getStatesForApiNode(node);

            QString caller = "No observation";

            if (!states.empty()) {
                /*
                 * Most recent observation.
                 */
                auto state = std::dynamic_pointer_cast<TypedState<duint>>(states.back());

                if (state) {
                    auto trace = state->getStackTrace();

                    if (trace) {
                        const auto& frames = trace->getFrames();

                        if (!frames.empty() && frames.front()) {
                            const auto& frame = frames.front();

                            const duint address = frame->getAddress();
                            const duint from = frame->getFrom();
                            const std::string comment = frame->getComment();

                            if (from != 0) {
                                caller = formatAddress(from);
                            } else if (!comment.empty()) {
                                caller = QString::fromStdString(comment);
                            } else {
                                caller = formatAddress(address);
                            }
                        } else {
                            caller = "Trace has no frames";
                        }
                    } else {
                        caller = "State has no trace";
                    }
                } else {
                    caller = "TypedState<duint> cast failed";
                }
            } else {
                caller = "No states for API node";
            }

            /*
             * Put the state information in the tooltip temporarily.
             */
            apiItem->setToolTip(QString("API: %1\nStates: %2\nCaller: %3")
                                    .arg(QString::fromStdString(node->getApiName()))
                                    .arg(static_cast<qulonglong>(states.size()))
                                    .arg(caller));

            /*
             * Immediate caller
             */
            auto* callerItem = new QTableWidgetItem(caller);

            callerItem->setToolTip(caller);

            apiTable->setItem(row, 0, callerItem);
        }

        if (apiTable->rowCount() > 0)
            apiTable->selectRow(0);
    }

    void populateStates(Nodes::ApiNodePtr apiNode) {
        stateSelector->clear();

        argumentsView->clear();
        stackView->clear();

        StatePtrList states = match->getStatesForApiNode(apiNode);

        if (states.empty()) {
            stateSelector->addItem("No observations");

            stateSelector->setEnabled(false);

            return;
        }

        stateSelector->setEnabled(true);

        /*
         * Every historical state is selectable.
         */
        for (size_t i = 0; i < states.size(); ++i) {
            QString caller = "Unknown";

            auto state = std::dynamic_pointer_cast<TypedState<duint>>(states[i]);

            if (state) {
                auto trace = state->getStackTrace();

                if (trace) {
                    const auto& frames = trace->getFrames();

                    if (!frames.empty() && frames.front()) {
                        const auto [address, from, to, comment] = frames.front()->getContent();

                        if (from != 0) {
                            caller = formatAddress(from);
                        } else if (!comment.empty()) {
                            caller = QString::fromStdString(comment);
                        } else {
                            caller = formatAddress(address);
                        }
                    }
                }
            }

            stateSelector->addItem(QString("#%1  %2").arg(i + 1).arg(caller));
        }

        stateSelector->setCurrentIndex(0);
    }

    void showState(int index) {
        argumentsView->clear();
        stackView->clear();

        const int row = apiTable->currentRow();

        if (row < 0 || row >= static_cast<int>(orderedApiNodes.size()))
            return;

        const auto& node = orderedApiNodes[row];

        StatePtrList states = match->getStatesForApiNode(node);

        if (index < 0 || index >= static_cast<int>(states.size()))
            return;

        /*
         * State -> TypedState<duint>
         */
        auto state = std::dynamic_pointer_cast<TypedState<duint>>(states[index]);

        if (!state)
            return;

        /*
         * --------------------------------------------------------
         * Arguments
         * --------------------------------------------------------
         */
        auto arguments = state->getArguments();

        if (arguments) {
            const auto values = arguments->getArguments();

            for (size_t i = 0; i < values.size(); ++i) {
                if (!values[i])
                    continue;

                argumentsView->appendPlainText(QString("arg%1 = %2")
                                                   .arg(static_cast<qulonglong>(i + 1))
                                                   .arg(formatBytes(values[i]->getBytes())));
            }
        }

        /*
         * --------------------------------------------------------
         * Stack trace
         * --------------------------------------------------------
         */
        auto trace = state->getStackTrace();

        if (!trace)
            return;

        const auto& frames = trace->getFrames();

        for (size_t i = 0; i < frames.size(); ++i) {
            if (!frames[i])
                continue;

            const auto& frame = frames[i];

            const duint address = frame->getAddress();
            const duint from = frame->getFrom();
            const duint to = frame->getTo();
            const std::string comment = frame->getComment();

            QString line = QString("#%1  ").arg(static_cast<qulonglong>(i));

            /*
             * Prefer the resolved symbol/comment.
             */
            if (!comment.empty()) {
                line += QString::fromStdString(comment);
            } else {
                line += formatAddress(address);
            }

            /*
             * Show the actual frame addresses as well.
             *
             * This is useful while we verify what the tracer is
             * producing.
             */
            line += QString("    [from %1 -> %2]").arg(formatAddress(from)).arg(formatAddress(to));

            stackView->appendPlainText(line);
        }
    }
};

/*
 * ------------------------------------------------------------
 * Matches window
 * ------------------------------------------------------------
 */
class MatchesDialog final : public QDialog {
  public:
    explicit MatchesDialog(QWidget* parent = nullptr) : QDialog(parent) {

        setWindowTitle("Capability Matches");

        resize(900, 500);

        setStyleSheet(capabilityStyleSheet());

        auto* layout = new QVBoxLayout(this);

        layout->setContentsMargins(14, 14, 14, 14);
        layout->setSpacing(10);

        /*
         * Header
         */

        auto* header = new QWidget(this);

        auto* headerLayout = new QHBoxLayout(header);

        headerLayout->setContentsMargins(0, 0, 0, 0);

        auto* title = new QLabel("Capability Matches", header);

        title->setProperty("class", "title");

        headerLayout->addWidget(title);

        headerLayout->addStretch();

        auto* hint = new QLabel("Double-click a match to inspect it", header);

        hint->setProperty("class", "subtitle");

        headerLayout->addWidget(hint);

        layout->addWidget(header);

        /*
         * Table
         */

        table = new QTableWidget(this);

        table->setColumnCount(3);

        table->setHorizontalHeaderLabels({"Rule", "TID", "APIs"});

        table->setSelectionBehavior(QAbstractItemView::SelectRows);

        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table->setWordWrap(false);

        table->verticalHeader()->hide();

        table->verticalHeader()->setDefaultSectionSize(29);

        auto* headerView = table->horizontalHeader();

        headerView->setSectionResizeMode(0, QHeaderView::Stretch);

        headerView->setSectionResizeMode(1, QHeaderView::Fixed);

        headerView->setSectionResizeMode(2, QHeaderView::Stretch);

        table->setColumnWidth(1, 75);

        layout->addWidget(table);

        /*
         * Double-click
         */

        connect(table, &QTableWidget::cellDoubleClicked, this, [this](int row, int) {
            if (row < 0 || row >= static_cast<int>(matches.size())) {

                return;
            }

            openMatch(matches[row]);
        });
    }

    void addMatch(const std::shared_ptr<Match>& match) {

        if (!match)
            return;

        Rule* rule = match->getRule();

        if (!rule)
            return;

        matches.push_back(match);

        const int row = table->rowCount();

        table->insertRow(row);

        /*
         * Rule
         */

        auto* ruleItem = new QTableWidgetItem(QString::fromStdString(rule->getName()));

        /*
         * TID
         */

        auto* tidItem = new QTableWidgetItem(QString::number(match->getThreadId()));

        tidItem->setTextAlignment(Qt::AlignCenter);

        /*
         * APIs
         */

        QStringList apiNames;

        for (const auto& node : *rule->getOrderedApiCallNodes()) {

            apiNames << QString::fromStdString(node->getApiName());
        }

        auto* apiItem = new QTableWidgetItem(apiNames.join("  →  "));

        ruleItem->setToolTip(QString::fromStdString(rule->getName()));

        apiItem->setToolTip(apiNames.join(", "));

        table->setItem(row, 0, ruleItem);

        table->setItem(row, 1, tidItem);

        table->setItem(row, 2, apiItem);

        table->selectRow(row);

        table->scrollToItem(ruleItem, QAbstractItemView::PositionAtBottom);
    }

  private:
    QTableWidget* table = nullptr;

    std::vector<std::shared_ptr<Match>> matches;

    void openMatch(const std::shared_ptr<Match>& match) {

        auto* dialog = new RuleMatchDialog(match);

        dialog->setAttribute(Qt::WA_DeleteOnClose);

        dialog->setWindowModality(Qt::NonModal);

        dialog->show();
        dialog->raise();
        dialog->activateWindow();
    }
};

static MatchesDialog* matchesDialog = nullptr;

enum RuleRoles { RuleIndexRole = Qt::UserRole, RuleActiveRole = Qt::UserRole + 1 };
class StatusDotDelegate final : public QStyledItemDelegate {
  public:
    explicit StatusDotDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const override {

        QStyleOptionViewItem opt(option);

        initStyleOption(&opt, index);

        if (index.column() == 0) {
            opt.text.clear();
            opt.icon = QIcon();
        }

        QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

        if (index.column() != 0)
            return;

        const bool active = index.data(RuleActiveRole).toBool();

        painter->save();

        painter->setRenderHint(QPainter::Antialiasing, true);

        const QColor color = active ? QColor("#4ecb71") : QColor("#656970");

        const QColor border = active ? QColor("#75e29a") : QColor("#858991");

        const QPoint center = option.rect.center();

        constexpr int diameter = 10;

        const QRectF rect(center.x() - diameter / 2.0, center.y() - diameter / 2.0, diameter,
                          diameter);

        painter->setPen(QPen(border, 1));

        painter->setBrush(color);

        painter->drawEllipse(rect);

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

        timer = new QTimer(this);

        connect(timer, &QTimer::timeout, this, [this]() {
            refresh();
            ProcessPendingMatches();
        });

        timer->start(100);

        refresh();
    }

    ~CapabilityView() override {
        if (timer)
            timer->stop();
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
    QTimer* timer = nullptr;

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
        setStyleSheet(capabilityStyleSheet());

        auto* layout = new QVBoxLayout(this);

        layout->setContentsMargins(10, 10, 10, 10);

        layout->setSpacing(8);

        /*
         * ------------------------------------------------------------
         * Header
         * ------------------------------------------------------------
         */

        auto* header = new QWidget(this);

        auto* headerLayout = new QHBoxLayout(header);

        headerLayout->setContentsMargins(4, 2, 4, 2);

        headerLayout->setSpacing(8);

        auto* title = new QLabel("Capabilities", header);

        title->setProperty("class", "title");

        headerLayout->addWidget(title);

        headerLayout->addStretch();

        auto* hint =
            new QLabel("Insert: add rule   •   Enter: rename   •   Delete: remove", header);

        hint->setProperty("class", "subtitle");

        headerLayout->addWidget(hint);

        layout->addWidget(header);

        /*
         * ------------------------------------------------------------
         * Table
         * ------------------------------------------------------------
         */

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

        table->setColumnCount(4);

        table->setHorizontalHeaderLabels({"Active", "Name", "Matches by TID", "Expression"});

        table->setSortingEnabled(false);

        table->setWordWrap(false);

        table->setTextElideMode(Qt::ElideRight);

        table->setSelectionBehavior(QAbstractItemView::SelectRows);

        table->setSelectionMode(QAbstractItemView::SingleSelection);

        table->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table->setAlternatingRowColors(true);

        table->verticalHeader()->hide();

        table->verticalHeader()->setDefaultSectionSize(29);

        /*
         * Header
         */

        QHeaderView* headerView = table->horizontalHeader();

        headerView->setHighlightSections(false);

        headerView->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        /*
         * Active
         */

        headerView->setSectionResizeMode(0, QHeaderView::Fixed);

        table->setColumnWidth(0, 77);

        /*
         * Name
         */

        headerView->setSectionResizeMode(1, QHeaderView::Interactive);

        table->setColumnWidth(1, 220);

        /*
         * TID
         */

        headerView->setSectionResizeMode(2, QHeaderView::Interactive);

        table->setColumnWidth(2, 155);

        /*
         * Expression
         */

        headerView->setSectionResizeMode(3, QHeaderView::Stretch);

        /*
         * Sort indicator
         */

        headerView->setSortIndicatorShown(true);

        headerView->setSortIndicator(1, nameSortOrder);

        /*
         * Status delegate
         */

        table->setItemDelegate(new StatusDotDelegate(table));

        layout->addWidget(table);

        /*
         * ------------------------------------------------------------
         * Events
         * ------------------------------------------------------------
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

        connect(table, &QTableWidget::cellDoubleClicked, this, [this](int row, int column) {
            if (column == 1)
                renameRule(row);
        });

        connect(headerView, &QHeaderView::sectionClicked, this, [this, headerView](int section) {
            if (section != 1)
                return;

            nameSortOrder =
                nameSortOrder == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder;

            headerView->setSortIndicator(1, nameSortOrder);

            table->sortItems(1, nameSortOrder);
        });

        table->viewport()->installEventFilter(this);

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

void ShowRuleMatch(const std::shared_ptr<Match>& match) {
    if (!match)
        return;

    QMutexLocker locker(&matchMutex);
    pendingMatches.push_back(match);
}

static CapabilityView* capabilityView = nullptr;

void CreateCapabilityView() {
    if (capabilityView)
        return;

    capabilityView = new CapabilityView();

    capabilityView->setAttribute(Qt::WA_DeleteOnClose, false);

    GuiAddQWidgetTab(capabilityView);
}

void DestroyCapabilityView() {
    /*
     * This function must execute on the Qt GUI thread.
     */

    if (matchesDialog) {
        auto* dialog = matchesDialog;
        matchesDialog = nullptr;

        dialog->close();
        delete dialog;
    }

    if (capabilityView) {
        auto* view = capabilityView;
        capabilityView = nullptr;

        /*
         * Stop the timer before removing the widget.
         */
        view->close();

        /*
         * Remove it from x64dbg's Qt widget/tab system.
         */
        GuiCloseQWidgetTab(view);

        /*
         * Deterministic destruction. Do NOT use deleteLater()
         * during plugin shutdown.
         */
        delete view;
    }
}

void RefreshCapabilityView() {
    if (!capabilityView)
        return;

    capabilityView->refresh();
}

void ProcessPendingMatches() {
    std::vector<std::shared_ptr<Match>> matches;

    {
        QMutexLocker locker(&matchMutex);
        matches.swap(pendingMatches);
    }

    if (matches.empty())
        return;

    if (!matchesDialog) {
        matchesDialog = new MatchesDialog();

        matchesDialog->setAttribute(Qt::WA_DeleteOnClose);
        matchesDialog->setWindowModality(Qt::NonModal);
    }

    for (const auto& match : matches)
        matchesDialog->addMatch(match);

    matchesDialog->show();
    matchesDialog->raise();
    matchesDialog->activateWindow();
}

void ClearPendingMatches() {
    QMutexLocker locker(&matchMutex);
    pendingMatches.clear();
}
