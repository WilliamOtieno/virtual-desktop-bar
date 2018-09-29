#ifndef VIRTUALDESKTOPBAR_H
#define VIRTUALDESKTOPBAR_H

#include <QObject>
#include <QVariantList>
#include <netwm.h>
#include <QX11Info>
#include <QAction>
#include <KActionCollection>

class VirtualDesktopBar : public QObject {
    Q_OBJECT

public:
    VirtualDesktopBar(QObject* parent = nullptr);

    Q_INVOKABLE const QVariantList getDesktopNames() const;
    Q_INVOKABLE const QVariant getCurrentDesktopName() const;
    Q_INVOKABLE const QVariant getCurrentDesktopNumber() const;

    Q_INVOKABLE void switchToDesktop(const int desktopNumber);
    Q_INVOKABLE void switchToRecentDesktop();

    Q_INVOKABLE void addNewDesktop(const QString desktopName = QString());

    Q_INVOKABLE void removeDesktop(const int desktopNumber = 0);
    Q_INVOKABLE void removeCurrentDesktop();
    Q_INVOKABLE void removeLastDesktop();

    Q_INVOKABLE void renameDesktop(const int desktopNumber, const QString desktopName);
    Q_INVOKABLE void renameCurrentDesktop(const QString desktopName);

    Q_INVOKABLE void swapDesktop(const int desktopNumber, const int targetDesktopNumber);
    Q_INVOKABLE void moveDesktop(const int desktopNumber, const int moveStep);
    Q_INVOKABLE void moveDesktopToLeft(const int desktopNumber);
    Q_INVOKABLE void moveDesktopToRight(const int desktopNumber);
    Q_INVOKABLE void moveCurrentDesktopToLeft();
    Q_INVOKABLE void moveCurrentDesktopToRight();

signals:
    void currentDesktopChanged(const int desktopNumber);
    void desktopAmountChanged(const int desktopAmount);

    void currentDesktopNameChangeRequested();
    void desktopRemoveRequested(int desktopNumber);
    void desktopNamesChanged();

private:
    NETRootInfo netRootInfo;

    KActionCollection* actionCollection;
    QAction* actionSwitchToRecentDesktop;
    QAction* actionAddNewDesktop;
    QAction* actionRemoveLastDesktop;
    QAction* actionRemoveCurrentDesktop;
    QAction* actionRenameCurrentDesktop;
    QAction* actionMoveCurrentDesktopToLeft;
    QAction* actionMoveCurrentDesktopToRight;

    void onCurrentDesktopChanged(const int desktopNumber);

    void setUpSignalForwarding();
    void setUpGlobalKeyboardShortcuts();

    const QList<WId> getWindows(const int desktopNumber, const bool afterDesktop = false);

    int currentDesktopNumber;
    int recentDesktopNumber;

    bool isFahoTilingLoaded();
    void refreshFahoTiling();
};

#endif // VIRTUALDESKTOPBAR_H