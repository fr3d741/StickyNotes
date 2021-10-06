#include <NoteRepository.h>

#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>

#include <filesystem>
#include <random>

static const char* SUBDIRECTORY = "data";

NoteRepository::NoteRepository() 
{
}

NoteRepository::~NoteRepository()
{
}

NoteRepository& NoteRepository::instance()
{
  static NoteRepository instance;
  return instance;
}

static QString generate() {
    static std::random_device dev;
    static std::mt19937 rng(dev());

    std::uniform_int_distribution<int> dist(0, 15);

    const char* v = "0123456789qwertyuiopasdfghjklzxcvbnm";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    QString res;
    for (int i = 0; i < 16; i++) {
        res += v[dist(rng)];
        res += v[dist(rng)];
    }

    return res;
}

QString NoteRepository::generateId()
{
    QString ret = generate();
    while (notes_.contains(ret))
        ret = generate();

    return ret;
}

void NoteRepository::store(const QString& id, const QString& content)
{
    notes_[id] = content;
}

QString NoteRepository::load(const QString& id) const
{
    return notes_[id];
}

QMap<QString, QString> NoteRepository::getNoteTitles()
{
    QMap<QString, QString> map;
    for (auto it = notes_.begin(); it != notes_.end(); ++it)
    {
        QTextStream stream(&it.value());
        map[it.key()] = stream.readLine();
    }

    return map;
}

static void makeSureDirExists() {

    QFileInfo info(SUBDIRECTORY);
    if (!info.exists())
    {
        QDir dir;
        dir.mkdir(SUBDIRECTORY);
    }
}

void NoteRepository::saveNotes() {

    makeSureDirExists();

    for (auto it = notes_.begin(); it != notes_.end(); ++it) {

        const QString filename = QString("%1/%2").arg(SUBDIRECTORY).arg(it.key());
        QFile file(filename);
        file.open(QIODeviceBase::WriteOnly);
        if (!file.isOpen()) {
            qDebug() << "Saving file not open";
            return;
        }
        
        QTextStream wrapper(&it.value(), QIODeviceBase::ReadOnly);
        QTextStream output(&file);
        while (!wrapper.atEnd())
            output << wrapper.readLine() << "\n";
    }
}

void NoteRepository::loadNotes() {

    notes_.clear();

    QDir dir = QDir(QString(SUBDIRECTORY));
    auto is_exist = dir.exists();
    auto path = dir.absolutePath();
    if (path.isEmpty() || !is_exist)
        return;
    auto entry_list = dir.entryInfoList();
    for (auto it : entry_list) {

        if (!it.isFile())
            continue;

        QFile file(it.filePath());
        file.open(QIODeviceBase::ReadOnly);
        if (!file.isOpen()) {
            qDebug() << "Loading file not open";
            return;
        }
        
        QTextStream input(&file);
        QString content = input.readAll();

        notes_[it.fileName()] = content;
    }
}
