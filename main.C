/*
    realizado por José Ruiz en Mayo de 2015
*/

# include <QApplication>
# include <mainwindow.H>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    QTextCodec * textCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(textCodec);
    QTextCodec::setCodecForLocale(textCodec);
    QTextCodec::setCodecForTr(textCodec);

    QLocale::setDefault(QLocale(QLocale::Spanish, QLocale::Venezuela));

    MainWindow mw;

    mw.show();

    return app.exec();
}
