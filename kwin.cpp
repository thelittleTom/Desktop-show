#include "kwin.h"

#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusPendingCallWatcher>
#include <QtDBus/QDBusPendingReply>
#include<QtDBus/QDBusPendingCall>


#include <QtDBus/QDBusError>

#include <QtDBus/QDBusInterface>

#include <QtDBus/QDBusReply>
#include<QDebug>
Kwin::Kwin(QObject *parent) : QObject(parent)
{
     selectWindow();
}
void Kwin :: selectWindow (){
 QDBusMessage message = QDBusMessage::createMethodCall ( QStringLiteral ("org.ukui.KWin"),
                                                         QStringLiteral ("/KWin"),
                                                         QStringLiteral ("org.ukui.KWin"),
                                                         QStringLiteral ("queryWindowInfo"));


// QDBusPendingReply < QVariantMap > async = QDBusConnection::sessionBus ().asyncCall(message);

// QDBusPendingCallWatcher * callWatcher = new QDBusPendingCallWatcher ( async , this );
// connect ( callWatcher ,& QDBusPendingCallWatcher::finished , this ,
//[ this ](QDBusPendingCallWatcher* self ){
//            QDBusPendingReply < QVariantMap > reply =* self ; self->deleteLater ();
//            if (!reply.isValid()){
////            emit detectionDone ( false );
//                return ;
//            }
//            auto m_windowInfo = reply.value ();
//            qDebug()<<m_windowInfo;
//         });

}
