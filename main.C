# include <QApplication>
# include <mainwindow.H>
# include <QTabWidget>

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
