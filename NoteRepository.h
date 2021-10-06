#pragma once

#include <QString>
#include <QMap>

#include <INoteRepository.h>

class NoteRepository : public INoteRepository {
  QMap<QString, QString> notes_;

  NoteRepository();
  NoteRepository(const NoteRepository&) = delete;
  NoteRepository(NoteRepository&&) = delete;

public:
  ~NoteRepository();

  static NoteRepository& instance();

  virtual QString generateId() override;
  virtual void store(const QString& id, const QString& content) override;
  virtual QString load(const QString& id) const override;

  QMap<QString, QString> getNoteTitles();

  void saveNotes();
  void loadNotes();
};
