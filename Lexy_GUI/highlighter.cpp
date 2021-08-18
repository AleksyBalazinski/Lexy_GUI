#include "highlighter.h"

Highlighter::Highlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    const QString keywordPatterns[] =
    {
        QStringLiteral("\\bvar\\b"), QStringLiteral("\\band\\b"), QStringLiteral("\\belse\\b"),
        QStringLiteral("\\bfalse\\b"), QStringLiteral("\\btrue\\b"), QStringLiteral("\\bif\\b"),
        QStringLiteral("\\bnil\\b"), QStringLiteral("\\bor\\b"), QStringLiteral("\\bprint\\b"),
        QStringLiteral("\\bwhile\\b")
    };

    for(const QString& pattern : keywordPatterns)
    {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // string literals
    quotationFormat.setFontItalic(true);
    quotationFormat.setForeground(Qt::darkCyan);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // comments
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

}

void Highlighter::highlightBlock(const QString &text)
{
    for(const HighlightingRule& rule : qAsConst(highlightingRules))
    {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while(matchIterator.hasNext())
        {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
