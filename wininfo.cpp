#include "wininfo.h"
inline QString exesc(char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    QString result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
    }
    pclose(pipe);
    return result;
}
wininfo::wininfo()
{
    iffinished=true;
    ijk=0;
    curindex=2;
    connect(&process2, SIGNAL(signal_finish_read()), this, SLOT(ready2()));

}
void wininfo::ifmaxscreen(){
    act_id= exesc("xprop -root | awk '/_NET_ACTIVE_WINDOW\\(WINDOW\\)/{print $NF}'");
    qDebug()<<act_id;
    QString ord="xwininfo -id "+act_id+ " -all";
    qDebug()<<ord;
    curindex=2;
    process2.startprocess(ord);
}
void wininfo::ready2(){
    QString str = process2.res;
    QString s ="Window state:\n          Maximized Vert\n          Maximized Horz\n";
    bool ifmax=str.contains(s,Qt::CaseSensitive);
    if(ifmax){
        s+="          Hidden\n";
        if(!str.contains(s,Qt::CaseSensitive)){
            emit signal_true();
            qDebug()<<true;
            iffinished=true;
            return;
        }
    }

        emit signal_false();

}
