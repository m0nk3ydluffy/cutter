
#include "SelectionHighlight.h"
#include "Configuration.h"

#include <QList>
#include <QTextEdit>
#include <QColor>
#include <QTextCursor>
#include <QPlainTextEdit>

QList<QTextEdit::ExtraSelection> createSameWordsSelections(QPlainTextEdit *textEdit, const QString &word)
{
    QList<QTextEdit::ExtraSelection> selections;
    QTextEdit::ExtraSelection highlightSelection;
    QTextDocument *document = textEdit->document();
    QColor highlightWordColor = ConfigColor("wordHighlight");

    if (word.isEmpty()) {
        return QList<QTextEdit::ExtraSelection>();
    }

    highlightSelection.cursor = textEdit->textCursor();
    highlightSelection.cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);

    while (!highlightSelection.cursor.isNull() && !highlightSelection.cursor.atEnd()) {
        highlightSelection.cursor = document->find(word, highlightSelection.cursor,
                                                   QTextDocument::FindWholeWords);

        if (!highlightSelection.cursor.isNull()) {
            highlightSelection.format.setBackground(highlightWordColor);

            selections.append(highlightSelection);
        }
    }
    return selections;
}

QTextEdit::ExtraSelection createLineHighlightSelection(const QTextCursor &cursor)
{
    QColor highlightColor = ConfigColor("lineHighlight");
    QTextEdit::ExtraSelection highlightSelection;
    highlightSelection.cursor = cursor;
    highlightSelection.format.setBackground(highlightColor);
    highlightSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
    highlightSelection.cursor.clearSelection();
    return highlightSelection;
}