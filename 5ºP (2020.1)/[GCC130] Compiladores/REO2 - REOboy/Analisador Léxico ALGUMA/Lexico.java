public class Lexico implements Constants
{
    private int position;
    private String input;

    public Lexico()
    {
        this(new java.io.StringReader(""));
    }

    public Lexico(java.io.Reader input)
    {
        setInput(input);
    }

    public void setInput(java.io.Reader input)
    {
        StringBuffer bfr = new StringBuffer();
        try
        {
            int c = input.read();
            while (c != -1)
            {
                bfr.append((char)c);
                c = input.read();
            }
            this.input = bfr.toString();
        }
        catch (java.io.IOException e)
        {
            e.printStackTrace();
        }

        setPosition(0);
    }

    public void setPosition(int pos)
    {
        position = pos;
    }

    public Token nextToken() throws LexicalError
    {
        if ( ! hasInput() )
            return null;

        int start = position;

        int state = 0;
        int lastState = 0;
        int endState = -1;
        int end = -1;

        while (hasInput())
        {
            lastState = state;
            state = nextState(nextChar(), state);

            if (state < 0)
                break;

            else
            {
                if (tokenForState(state) >= 0)
                {
                    endState = state;
                    end = position;
                }
            }
        }
        if (endState < 0 || (endState != state && tokenForState(lastState) == -2))
            throw new LexicalError(SCANNER_ERROR[lastState], start);

        position = end;

        int token = tokenForState(endState);

        if (token == 0)
            return nextToken();
        else
        {
            String lexeme = input.substring(start, end);
            return new Token(token, lexeme, start);
        }
    }

    private int nextState(char c, int state)
    {
        switch (state)
        {
            case 0:
                switch (c)
                {
                    case 9: return 1;
                    case 10: return 1;
                    case 13: return 1;
                    case 32: return 1;
                    case 34: return 2;
                    case 37: return 3;
                    case 40: return 4;
                    case 41: return 5;
                    case 42: return 6;
                    case 43: return 7;
                    case 45: return 7;
                    case 47: return 6;
                    case 48: return 8;
                    case 49: return 8;
                    case 50: return 8;
                    case 51: return 8;
                    case 52: return 8;
                    case 53: return 8;
                    case 54: return 8;
                    case 55: return 8;
                    case 56: return 8;
                    case 57: return 8;
                    case 58: return 9;
                    case 60: return 10;
                    case 61: return 11;
                    case 62: return 12;
                    case 65: return 13;
                    case 68: return 14;
                    case 69: return 15;
                    case 70: return 16;
                    case 73: return 17;
                    case 76: return 18;
                    case 79: return 19;
                    case 82: return 20;
                    case 83: return 21;
                    case 97: return 22;
                    case 98: return 22;
                    case 99: return 22;
                    case 100: return 22;
                    case 101: return 22;
                    case 102: return 22;
                    case 103: return 22;
                    case 104: return 22;
                    case 105: return 22;
                    case 106: return 22;
                    case 107: return 22;
                    case 108: return 22;
                    case 109: return 22;
                    case 110: return 22;
                    case 111: return 22;
                    case 112: return 22;
                    case 113: return 22;
                    case 114: return 22;
                    case 115: return 22;
                    case 116: return 22;
                    case 117: return 22;
                    case 118: return 22;
                    case 119: return 22;
                    case 120: return 22;
                    case 121: return 22;
                    case 122: return 22;
                    default: return -1;
                }
            case 2:
                switch (c)
                {
                    case 9: return 2;
                    case 32: return 2;
                    case 33: return 2;
                    case 34: return 23;
                    case 35: return 2;
                    case 36: return 2;
                    case 37: return 2;
                    case 38: return 2;
                    case 39: return 2;
                    case 40: return 2;
                    case 41: return 2;
                    case 42: return 2;
                    case 43: return 2;
                    case 44: return 2;
                    case 45: return 2;
                    case 46: return 2;
                    case 47: return 2;
                    case 48: return 2;
                    case 49: return 2;
                    case 50: return 2;
                    case 51: return 2;
                    case 52: return 2;
                    case 53: return 2;
                    case 54: return 2;
                    case 55: return 2;
                    case 56: return 2;
                    case 57: return 2;
                    case 58: return 2;
                    case 59: return 2;
                    case 60: return 2;
                    case 61: return 2;
                    case 62: return 2;
                    case 63: return 2;
                    case 64: return 2;
                    case 65: return 2;
                    case 66: return 2;
                    case 67: return 2;
                    case 68: return 2;
                    case 69: return 2;
                    case 70: return 2;
                    case 71: return 2;
                    case 72: return 2;
                    case 73: return 2;
                    case 74: return 2;
                    case 75: return 2;
                    case 76: return 2;
                    case 77: return 2;
                    case 78: return 2;
                    case 79: return 2;
                    case 80: return 2;
                    case 81: return 2;
                    case 82: return 2;
                    case 83: return 2;
                    case 84: return 2;
                    case 85: return 2;
                    case 86: return 2;
                    case 87: return 2;
                    case 88: return 2;
                    case 89: return 2;
                    case 90: return 2;
                    case 91: return 2;
                    case 92: return 2;
                    case 93: return 2;
                    case 94: return 2;
                    case 95: return 2;
                    case 96: return 2;
                    case 97: return 2;
                    case 98: return 2;
                    case 99: return 2;
                    case 100: return 2;
                    case 101: return 2;
                    case 102: return 2;
                    case 103: return 2;
                    case 104: return 2;
                    case 105: return 2;
                    case 106: return 2;
                    case 107: return 2;
                    case 108: return 2;
                    case 109: return 2;
                    case 110: return 2;
                    case 111: return 2;
                    case 112: return 2;
                    case 113: return 2;
                    case 114: return 2;
                    case 115: return 2;
                    case 116: return 2;
                    case 117: return 2;
                    case 118: return 2;
                    case 119: return 2;
                    case 120: return 2;
                    case 121: return 2;
                    case 122: return 2;
                    case 123: return 2;
                    case 124: return 2;
                    case 125: return 2;
                    case 126: return 2;
                    case 161: return 2;
                    case 162: return 2;
                    case 163: return 2;
                    case 164: return 2;
                    case 165: return 2;
                    case 166: return 2;
                    case 167: return 2;
                    case 168: return 2;
                    case 169: return 2;
                    case 170: return 2;
                    case 171: return 2;
                    case 172: return 2;
                    case 173: return 2;
                    case 174: return 2;
                    case 175: return 2;
                    case 176: return 2;
                    case 177: return 2;
                    case 178: return 2;
                    case 179: return 2;
                    case 180: return 2;
                    case 181: return 2;
                    case 182: return 2;
                    case 183: return 2;
                    case 184: return 2;
                    case 185: return 2;
                    case 186: return 2;
                    case 187: return 2;
                    case 188: return 2;
                    case 189: return 2;
                    case 190: return 2;
                    case 191: return 2;
                    case 192: return 2;
                    case 193: return 2;
                    case 194: return 2;
                    case 195: return 2;
                    case 196: return 2;
                    case 197: return 2;
                    case 198: return 2;
                    case 199: return 2;
                    case 200: return 2;
                    case 201: return 2;
                    case 202: return 2;
                    case 203: return 2;
                    case 204: return 2;
                    case 205: return 2;
                    case 206: return 2;
                    case 207: return 2;
                    case 208: return 2;
                    case 209: return 2;
                    case 210: return 2;
                    case 211: return 2;
                    case 212: return 2;
                    case 213: return 2;
                    case 214: return 2;
                    case 215: return 2;
                    case 216: return 2;
                    case 217: return 2;
                    case 218: return 2;
                    case 219: return 2;
                    case 220: return 2;
                    case 221: return 2;
                    case 222: return 2;
                    case 223: return 2;
                    case 224: return 2;
                    case 225: return 2;
                    case 226: return 2;
                    case 227: return 2;
                    case 228: return 2;
                    case 229: return 2;
                    case 230: return 2;
                    case 231: return 2;
                    case 232: return 2;
                    case 233: return 2;
                    case 234: return 2;
                    case 235: return 2;
                    case 236: return 2;
                    case 237: return 2;
                    case 238: return 2;
                    case 239: return 2;
                    case 240: return 2;
                    case 241: return 2;
                    case 242: return 2;
                    case 243: return 2;
                    case 244: return 2;
                    case 245: return 2;
                    case 246: return 2;
                    case 247: return 2;
                    case 248: return 2;
                    case 249: return 2;
                    case 250: return 2;
                    case 251: return 2;
                    case 252: return 2;
                    case 253: return 2;
                    case 254: return 2;
                    case 255: return 2;
                    default: return -1;
                }
            case 3:
                switch (c)
                {
                    case 9: return 3;
                    case 10: return 1;
                    case 32: return 3;
                    case 33: return 3;
                    case 34: return 3;
                    case 35: return 3;
                    case 36: return 3;
                    case 37: return 3;
                    case 38: return 3;
                    case 39: return 3;
                    case 40: return 3;
                    case 41: return 3;
                    case 42: return 3;
                    case 43: return 3;
                    case 44: return 3;
                    case 45: return 3;
                    case 46: return 3;
                    case 47: return 3;
                    case 48: return 3;
                    case 49: return 3;
                    case 50: return 3;
                    case 51: return 3;
                    case 52: return 3;
                    case 53: return 3;
                    case 54: return 3;
                    case 55: return 3;
                    case 56: return 3;
                    case 57: return 3;
                    case 58: return 3;
                    case 59: return 3;
                    case 60: return 3;
                    case 61: return 3;
                    case 62: return 3;
                    case 63: return 3;
                    case 64: return 3;
                    case 65: return 3;
                    case 66: return 3;
                    case 67: return 3;
                    case 68: return 3;
                    case 69: return 3;
                    case 70: return 3;
                    case 71: return 3;
                    case 72: return 3;
                    case 73: return 3;
                    case 74: return 3;
                    case 75: return 3;
                    case 76: return 3;
                    case 77: return 3;
                    case 78: return 3;
                    case 79: return 3;
                    case 80: return 3;
                    case 81: return 3;
                    case 82: return 3;
                    case 83: return 3;
                    case 84: return 3;
                    case 85: return 3;
                    case 86: return 3;
                    case 87: return 3;
                    case 88: return 3;
                    case 89: return 3;
                    case 90: return 3;
                    case 91: return 3;
                    case 92: return 3;
                    case 93: return 3;
                    case 94: return 3;
                    case 95: return 3;
                    case 96: return 3;
                    case 97: return 3;
                    case 98: return 3;
                    case 99: return 3;
                    case 100: return 3;
                    case 101: return 3;
                    case 102: return 3;
                    case 103: return 3;
                    case 104: return 3;
                    case 105: return 3;
                    case 106: return 3;
                    case 107: return 3;
                    case 108: return 3;
                    case 109: return 3;
                    case 110: return 3;
                    case 111: return 3;
                    case 112: return 3;
                    case 113: return 3;
                    case 114: return 3;
                    case 115: return 3;
                    case 116: return 3;
                    case 117: return 3;
                    case 118: return 3;
                    case 119: return 3;
                    case 120: return 3;
                    case 121: return 3;
                    case 122: return 3;
                    case 123: return 3;
                    case 124: return 3;
                    case 125: return 3;
                    case 126: return 3;
                    case 161: return 3;
                    case 162: return 3;
                    case 163: return 3;
                    case 164: return 3;
                    case 165: return 3;
                    case 166: return 3;
                    case 167: return 3;
                    case 168: return 3;
                    case 169: return 3;
                    case 170: return 3;
                    case 171: return 3;
                    case 172: return 3;
                    case 173: return 3;
                    case 174: return 3;
                    case 175: return 3;
                    case 176: return 3;
                    case 177: return 3;
                    case 178: return 3;
                    case 179: return 3;
                    case 180: return 3;
                    case 181: return 3;
                    case 182: return 3;
                    case 183: return 3;
                    case 184: return 3;
                    case 185: return 3;
                    case 186: return 3;
                    case 187: return 3;
                    case 188: return 3;
                    case 189: return 3;
                    case 190: return 3;
                    case 191: return 3;
                    case 192: return 3;
                    case 193: return 3;
                    case 194: return 3;
                    case 195: return 3;
                    case 196: return 3;
                    case 197: return 3;
                    case 198: return 3;
                    case 199: return 3;
                    case 200: return 3;
                    case 201: return 3;
                    case 202: return 3;
                    case 203: return 3;
                    case 204: return 3;
                    case 205: return 3;
                    case 206: return 3;
                    case 207: return 3;
                    case 208: return 3;
                    case 209: return 3;
                    case 210: return 3;
                    case 211: return 3;
                    case 212: return 3;
                    case 213: return 3;
                    case 214: return 3;
                    case 215: return 3;
                    case 216: return 3;
                    case 217: return 3;
                    case 218: return 3;
                    case 219: return 3;
                    case 220: return 3;
                    case 221: return 3;
                    case 222: return 3;
                    case 223: return 3;
                    case 224: return 3;
                    case 225: return 3;
                    case 226: return 3;
                    case 227: return 3;
                    case 228: return 3;
                    case 229: return 3;
                    case 230: return 3;
                    case 231: return 3;
                    case 232: return 3;
                    case 233: return 3;
                    case 234: return 3;
                    case 235: return 3;
                    case 236: return 3;
                    case 237: return 3;
                    case 238: return 3;
                    case 239: return 3;
                    case 240: return 3;
                    case 241: return 3;
                    case 242: return 3;
                    case 243: return 3;
                    case 244: return 3;
                    case 245: return 3;
                    case 246: return 3;
                    case 247: return 3;
                    case 248: return 3;
                    case 249: return 3;
                    case 250: return 3;
                    case 251: return 3;
                    case 252: return 3;
                    case 253: return 3;
                    case 254: return 3;
                    case 255: return 3;
                    default: return -1;
                }
            case 7:
                switch (c)
                {
                    case 48: return 8;
                    case 49: return 8;
                    case 50: return 8;
                    case 51: return 8;
                    case 52: return 8;
                    case 53: return 8;
                    case 54: return 8;
                    case 55: return 8;
                    case 56: return 8;
                    case 57: return 8;
                    default: return -1;
                }
            case 8:
                switch (c)
                {
                    case 44: return 24;
                    case 48: return 8;
                    case 49: return 8;
                    case 50: return 8;
                    case 51: return 8;
                    case 52: return 8;
                    case 53: return 8;
                    case 54: return 8;
                    case 55: return 8;
                    case 56: return 8;
                    case 57: return 8;
                    default: return -1;
                }
            case 10:
                switch (c)
                {
                    case 61: return 11;
                    case 62: return 11;
                    default: return -1;
                }
            case 12:
                switch (c)
                {
                    case 61: return 11;
                    default: return -1;
                }
            case 13:
                switch (c)
                {
                    case 76: return 25;
                    case 84: return 26;
                    default: return -1;
                }
            case 14:
                switch (c)
                {
                    case 69: return 27;
                    default: return -1;
                }
            case 15:
                switch (c)
                {
                    case 78: return 28;
                    default: return -1;
                }
            case 16:
                switch (c)
                {
                    case 73: return 29;
                    default: return -1;
                }
            case 17:
                switch (c)
                {
                    case 77: return 30;
                    case 78: return 31;
                    default: return -1;
                }
            case 18:
                switch (c)
                {
                    case 69: return 32;
                    default: return -1;
                }
            case 19:
                switch (c)
                {
                    case 85: return 33;
                    default: return -1;
                }
            case 20:
                switch (c)
                {
                    case 69: return 34;
                    default: return -1;
                }
            case 21:
                switch (c)
                {
                    case 69: return 35;
                    default: return -1;
                }
            case 22:
                switch (c)
                {
                    case 48: return 22;
                    case 49: return 22;
                    case 50: return 22;
                    case 51: return 22;
                    case 52: return 22;
                    case 53: return 22;
                    case 54: return 22;
                    case 55: return 22;
                    case 56: return 22;
                    case 57: return 22;
                    case 65: return 22;
                    case 66: return 22;
                    case 67: return 22;
                    case 68: return 22;
                    case 69: return 22;
                    case 70: return 22;
                    case 71: return 22;
                    case 72: return 22;
                    case 73: return 22;
                    case 74: return 22;
                    case 75: return 22;
                    case 76: return 22;
                    case 77: return 22;
                    case 78: return 22;
                    case 79: return 22;
                    case 80: return 22;
                    case 81: return 22;
                    case 82: return 22;
                    case 83: return 22;
                    case 84: return 22;
                    case 85: return 22;
                    case 86: return 22;
                    case 87: return 22;
                    case 88: return 22;
                    case 89: return 22;
                    case 90: return 22;
                    case 97: return 22;
                    case 98: return 22;
                    case 99: return 22;
                    case 100: return 22;
                    case 101: return 22;
                    case 102: return 22;
                    case 103: return 22;
                    case 104: return 22;
                    case 105: return 22;
                    case 106: return 22;
                    case 107: return 22;
                    case 108: return 22;
                    case 109: return 22;
                    case 110: return 22;
                    case 111: return 22;
                    case 112: return 22;
                    case 113: return 22;
                    case 114: return 22;
                    case 115: return 22;
                    case 116: return 22;
                    case 117: return 22;
                    case 118: return 22;
                    case 119: return 22;
                    case 120: return 22;
                    case 121: return 22;
                    case 122: return 22;
                    default: return -1;
                }
            case 23:
                switch (c)
                {
                    case 9: return 2;
                    case 32: return 2;
                    case 33: return 2;
                    case 34: return 23;
                    case 35: return 2;
                    case 36: return 2;
                    case 37: return 2;
                    case 38: return 2;
                    case 39: return 2;
                    case 40: return 2;
                    case 41: return 2;
                    case 42: return 2;
                    case 43: return 2;
                    case 44: return 2;
                    case 45: return 2;
                    case 46: return 2;
                    case 47: return 2;
                    case 48: return 2;
                    case 49: return 2;
                    case 50: return 2;
                    case 51: return 2;
                    case 52: return 2;
                    case 53: return 2;
                    case 54: return 2;
                    case 55: return 2;
                    case 56: return 2;
                    case 57: return 2;
                    case 58: return 2;
                    case 59: return 2;
                    case 60: return 2;
                    case 61: return 2;
                    case 62: return 2;
                    case 63: return 2;
                    case 64: return 2;
                    case 65: return 2;
                    case 66: return 2;
                    case 67: return 2;
                    case 68: return 2;
                    case 69: return 2;
                    case 70: return 2;
                    case 71: return 2;
                    case 72: return 2;
                    case 73: return 2;
                    case 74: return 2;
                    case 75: return 2;
                    case 76: return 2;
                    case 77: return 2;
                    case 78: return 2;
                    case 79: return 2;
                    case 80: return 2;
                    case 81: return 2;
                    case 82: return 2;
                    case 83: return 2;
                    case 84: return 2;
                    case 85: return 2;
                    case 86: return 2;
                    case 87: return 2;
                    case 88: return 2;
                    case 89: return 2;
                    case 90: return 2;
                    case 91: return 2;
                    case 92: return 2;
                    case 93: return 2;
                    case 94: return 2;
                    case 95: return 2;
                    case 96: return 2;
                    case 97: return 2;
                    case 98: return 2;
                    case 99: return 2;
                    case 100: return 2;
                    case 101: return 2;
                    case 102: return 2;
                    case 103: return 2;
                    case 104: return 2;
                    case 105: return 2;
                    case 106: return 2;
                    case 107: return 2;
                    case 108: return 2;
                    case 109: return 2;
                    case 110: return 2;
                    case 111: return 2;
                    case 112: return 2;
                    case 113: return 2;
                    case 114: return 2;
                    case 115: return 2;
                    case 116: return 2;
                    case 117: return 2;
                    case 118: return 2;
                    case 119: return 2;
                    case 120: return 2;
                    case 121: return 2;
                    case 122: return 2;
                    case 123: return 2;
                    case 124: return 2;
                    case 125: return 2;
                    case 126: return 2;
                    case 161: return 2;
                    case 162: return 2;
                    case 163: return 2;
                    case 164: return 2;
                    case 165: return 2;
                    case 166: return 2;
                    case 167: return 2;
                    case 168: return 2;
                    case 169: return 2;
                    case 170: return 2;
                    case 171: return 2;
                    case 172: return 2;
                    case 173: return 2;
                    case 174: return 2;
                    case 175: return 2;
                    case 176: return 2;
                    case 177: return 2;
                    case 178: return 2;
                    case 179: return 2;
                    case 180: return 2;
                    case 181: return 2;
                    case 182: return 2;
                    case 183: return 2;
                    case 184: return 2;
                    case 185: return 2;
                    case 186: return 2;
                    case 187: return 2;
                    case 188: return 2;
                    case 189: return 2;
                    case 190: return 2;
                    case 191: return 2;
                    case 192: return 2;
                    case 193: return 2;
                    case 194: return 2;
                    case 195: return 2;
                    case 196: return 2;
                    case 197: return 2;
                    case 198: return 2;
                    case 199: return 2;
                    case 200: return 2;
                    case 201: return 2;
                    case 202: return 2;
                    case 203: return 2;
                    case 204: return 2;
                    case 205: return 2;
                    case 206: return 2;
                    case 207: return 2;
                    case 208: return 2;
                    case 209: return 2;
                    case 210: return 2;
                    case 211: return 2;
                    case 212: return 2;
                    case 213: return 2;
                    case 214: return 2;
                    case 215: return 2;
                    case 216: return 2;
                    case 217: return 2;
                    case 218: return 2;
                    case 219: return 2;
                    case 220: return 2;
                    case 221: return 2;
                    case 222: return 2;
                    case 223: return 2;
                    case 224: return 2;
                    case 225: return 2;
                    case 226: return 2;
                    case 227: return 2;
                    case 228: return 2;
                    case 229: return 2;
                    case 230: return 2;
                    case 231: return 2;
                    case 232: return 2;
                    case 233: return 2;
                    case 234: return 2;
                    case 235: return 2;
                    case 236: return 2;
                    case 237: return 2;
                    case 238: return 2;
                    case 239: return 2;
                    case 240: return 2;
                    case 241: return 2;
                    case 242: return 2;
                    case 243: return 2;
                    case 244: return 2;
                    case 245: return 2;
                    case 246: return 2;
                    case 247: return 2;
                    case 248: return 2;
                    case 249: return 2;
                    case 250: return 2;
                    case 251: return 2;
                    case 252: return 2;
                    case 253: return 2;
                    case 254: return 2;
                    case 255: return 2;
                    default: return -1;
                }
            case 24:
                switch (c)
                {
                    case 48: return 36;
                    case 49: return 36;
                    case 50: return 36;
                    case 51: return 36;
                    case 52: return 36;
                    case 53: return 36;
                    case 54: return 36;
                    case 55: return 36;
                    case 56: return 36;
                    case 57: return 36;
                    default: return -1;
                }
            case 25:
                switch (c)
                {
                    case 71: return 37;
                    default: return -1;
                }
            case 26:
                switch (c)
                {
                    case 82: return 38;
                    default: return -1;
                }
            case 27:
                switch (c)
                {
                    case 67: return 39;
                    default: return -1;
                }
            case 28:
                switch (c)
                {
                    case 81: return 40;
                    case 84: return 41;
                    default: return -1;
                }
            case 29:
                switch (c)
                {
                    case 77: return 42;
                    default: return -1;
                }
            case 30:
                switch (c)
                {
                    case 80: return 43;
                    default: return -1;
                }
            case 31:
                switch (c)
                {
                    case 73: return 44;
                    case 84: return 45;
                    default: return -1;
                }
            case 32:
                switch (c)
                {
                    case 82: return 46;
                    default: return -1;
                }
            case 34:
                switch (c)
                {
                    case 65: return 47;
                    default: return -1;
                }
            case 36:
                switch (c)
                {
                    case 48: return 36;
                    case 49: return 36;
                    case 50: return 36;
                    case 51: return 36;
                    case 52: return 36;
                    case 53: return 36;
                    case 54: return 36;
                    case 55: return 36;
                    case 56: return 36;
                    case 57: return 36;
                    default: return -1;
                }
            case 37:
                switch (c)
                {
                    case 79: return 48;
                    default: return -1;
                }
            case 38:
                switch (c)
                {
                    case 73: return 49;
                    default: return -1;
                }
            case 39:
                switch (c)
                {
                    case 76: return 50;
                    default: return -1;
                }
            case 40:
                switch (c)
                {
                    case 85: return 51;
                    default: return -1;
                }
            case 41:
                switch (c)
                {
                    case 65: return 52;
                    default: return -1;
                }
            case 43:
                switch (c)
                {
                    case 82: return 53;
                    default: return -1;
                }
            case 44:
                switch (c)
                {
                    case 67: return 54;
                    default: return -1;
                }
            case 45:
                switch (c)
                {
                    case 69: return 55;
                    default: return -1;
                }
            case 47:
                switch (c)
                {
                    case 76: return 56;
                    default: return -1;
                }
            case 48:
                switch (c)
                {
                    case 82: return 57;
                    default: return -1;
                }
            case 49:
                switch (c)
                {
                    case 66: return 58;
                    default: return -1;
                }
            case 50:
                switch (c)
                {
                    case 65: return 59;
                    default: return -1;
                }
            case 51:
                switch (c)
                {
                    case 65: return 60;
                    default: return -1;
                }
            case 52:
                switch (c)
                {
                    case 79: return 61;
                    default: return -1;
                }
            case 53:
                switch (c)
                {
                    case 73: return 62;
                    default: return -1;
                }
            case 54:
                switch (c)
                {
                    case 73: return 63;
                    default: return -1;
                }
            case 55:
                switch (c)
                {
                    case 73: return 64;
                    default: return -1;
                }
            case 57:
                switch (c)
                {
                    case 73: return 65;
                    default: return -1;
                }
            case 58:
                switch (c)
                {
                    case 85: return 66;
                    default: return -1;
                }
            case 59:
                switch (c)
                {
                    case 82: return 67;
                    default: return -1;
                }
            case 60:
                switch (c)
                {
                    case 78: return 68;
                    default: return -1;
                }
            case 62:
                switch (c)
                {
                    case 77: return 69;
                    default: return -1;
                }
            case 63:
                switch (c)
                {
                    case 79: return 70;
                    default: return -1;
                }
            case 64:
                switch (c)
                {
                    case 82: return 71;
                    default: return -1;
                }
            case 65:
                switch (c)
                {
                    case 84: return 72;
                    default: return -1;
                }
            case 66:
                switch (c)
                {
                    case 73: return 73;
                    default: return -1;
                }
            case 67:
                switch (c)
                {
                    case 65: return 74;
                    default: return -1;
                }
            case 68:
                switch (c)
                {
                    case 84: return 75;
                    default: return -1;
                }
            case 69:
                switch (c)
                {
                    case 73: return 76;
                    default: return -1;
                }
            case 71:
                switch (c)
                {
                    case 79: return 77;
                    default: return -1;
                }
            case 72:
                switch (c)
                {
                    case 77: return 78;
                    default: return -1;
                }
            case 73:
                switch (c)
                {
                    case 82: return 79;
                    default: return -1;
                }
            case 74:
                switch (c)
                {
                    case 67: return 80;
                    default: return -1;
                }
            case 75:
                switch (c)
                {
                    case 79: return 81;
                    default: return -1;
                }
            case 76:
                switch (c)
                {
                    case 82: return 82;
                    default: return -1;
                }
            case 78:
                switch (c)
                {
                    case 79: return 83;
                    default: return -1;
                }
            case 80:
                switch (c)
                {
                    case 79: return 84;
                    default: return -1;
                }
            case 84:
                switch (c)
                {
                    case 69: return 85;
                    default: return -1;
                }
            case 85:
                switch (c)
                {
                    case 83: return 86;
                    default: return -1;
                }
            default: return -1;
        }
    }

    private int tokenForState(int state)
    {
        if (state < 0 || state >= TOKEN_STATE.length)
            return -1;

        return TOKEN_STATE[state];
    }

    private boolean hasInput()
    {
        return position < input.length();
    }

    private char nextChar()
    {
        if (hasInput())
            return input.charAt(position++);
        else
            return (char) -1;
    }
}
