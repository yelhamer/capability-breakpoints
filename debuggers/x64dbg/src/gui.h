#ifndef GUI_H
#define GUI_H

#include "engine.h"

#include <QTableWidget>
#include <QWidget>
#include <memory>

class CapabilityView : public QWidget {
  public:
    explicit CapabilityView(QWidget* parent = nullptr);

    void refresh();

  private:
    QTableWidget* table = nullptr;

    void setupUi();
    void renameRule(int row);
    void showContextMenu(const QPoint& pos);
    void addRule();
    void deleteRule(int index);
};

void CreateCapabilityView();
void ProcessPendingMatches();
void DestroyCapabilityView();
void RefreshCapabilityView();
void ClearPendingMatches();
void ShowRuleMatch(const std::shared_ptr<Match>& match);

#endif // GUI_H
