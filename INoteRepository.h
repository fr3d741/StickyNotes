#pragma once

class INoteRepository {
public:
    virtual QString generateId() = 0;
    virtual void store(const QString& id, const QString& content) = 0;
    virtual QString load(const QString& id) const = 0;
};

