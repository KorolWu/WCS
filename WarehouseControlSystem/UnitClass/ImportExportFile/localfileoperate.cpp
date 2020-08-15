#include "localfileoperate.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

LocalFileOperate::LocalFileOperate()
{

}
///
/// \brief LocalFileOperate::ReadFileData
/// \param filename
/// \return
///
QList<QStringList> LocalFileOperate::ReadFileData(QString filename)
{
    QList<QStringList> listdata;
    QDir dir = QDir::current();
    QFile file(dir.filePath(filename));
    if(!file.open(QIODevice::ReadOnly))
        return  listdata;
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分
    for(int i = 0 ; i < tempOption.count() ; i++)
    {
         QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分
         if(tempbar.size() >=2)
        {
//             if(tempbar.contains(""))
//             {
//                 listdata.clear();
//                 return listdata;
//             }
             listdata.append(tempbar);
         }
    }
    file.close();//操作完成后记得关闭文件
    return listdata;
}
///
/// \brief LocalFileOperate::WriteFileData
/// \param Datalist
/// \param filename
/// \return
///
bool LocalFileOperate::WriteFileData(QList<QStringList> Datalist, QString filename,QStringList tableheadlist)
{
     //打开.csv文件
     QFile file(filename);
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
//         std::cerr << "Cannot open file for writing: "
//                   << qPrintable(file.errorString()) << std::endl;
         return false;
     }
     QTextStream out(&file);
     //获取数据
     for(int i = 0; i < tableheadlist.size(); ++i)
    {
          out << tableheadlist[i]<<",";
     }
       out << "\n";//表头
     //获取表格内容
     for(int i = 0; i < Datalist.size(); i ++)
     {
         for(int col = 0; col < Datalist[i].size(); col++)
         {
             QString string =  Datalist[i].at(col);
             out << string << ",";// 写入文件
         }
         out << "\n";
     }
     file.close();
     return true;
}
