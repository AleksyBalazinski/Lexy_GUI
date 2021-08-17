namespace utils
{
    bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    bool isAlpha(char c)
    {
        return c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isAlphaNumeric(char c)
    {
        return isDigit(c) || isAlpha(c);
    }
}
