#ifndef DOCUMENTSTATE_H
#define DOCUMENTSTATE_H

#include <QObject>
#include <QString>
#include <QDebug>

class DocumentState : public QObject
{
    Q_OBJECT

public:
    DocumentState() :
        _pathToTheFile(""),
        _textChangeFlag(false),
        _changesSavedFlag(true)
    {}

    void setPathToTheFile(const QString &path)
    {
        this->_pathToTheFile = path;
    }

    const QString & getPathToTheFile()
    {
        return this->_pathToTheFile;
    }

    bool isChangesSaved()
    {
        return this->_changesSavedFlag;
    }

    void clear()
    {
        this->_pathToTheFile.clear();
        this->_textChangeFlag = false;
        this->_changesSavedFlag = true;
    }

    ~DocumentState() {}

public slots:
    void slotTextChanged()
    {
        this->_textChangeFlag = true;
        this->_changesSavedFlag = false;
    }

    void slotChangesSaved()
    {
        this->_changesSavedFlag = true;
        this->_textChangeFlag = false;
    }

private:
    QString _pathToTheFile;
    bool _textChangeFlag;    // false - text is not changed, true - text is changed
    bool _changesSavedFlag;  // false - changes not saved, true - changes saved
};

#endif // DOCUMENTSTATE_H
