/*
Facebook/Amazon/TikTok/Sprinklr/Apple/Deutsche Bank/ServiceNow

Given a string queryIP, return "IPv4" if IP is a valid IPv4 address, "IPv6" if IP is a valid IPv6 address or "Neither" if IP is not a correct IP of any type.

A valid IPv4 address is an IP in the form "x1.x2.x3.x4" where 0 <= xi <= 255 and xi cannot contain leading zeros. For example, "192.168.1.1" and "192.168.1.0" are valid IPv4 addresses while "192.168.01.1", "192.168.1.00", and "192.168@1.1" are invalid IPv4 addresses.

A valid IPv6 address is an IP in the form "x1:x2:x3:x4:x5:x6:x7:x8" where:

1 <= xi.length <= 4
xi is a hexadecimal string which may contain digits, lowercase English letter ('a' to 'f') and upper-case English letters ('A' to 'F').
Leading zeros are allowed in xi.
For example, "2001:0db8:85a3:0000:0000:8a2e:0370:7334" and "2001:db8:85a3:0:0:8A2E:0370:7334" are valid IPv6 addresses, while "2001:0db8:85a3::8A2E:037j:7334" and "02001:0db8:85a3:0000:0000:8a2e:0370:7334" are invalid IPv6 addresses.

Example 1:

Input: queryIP = "172.16.254.1"
Output: "IPv4"
Explanation: This is a valid IPv4 address, return "IPv4".

Example 2:

Input: queryIP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
Output: "IPv6"
Explanation: This is a valid IPv6 address, return "IPv6".

Example 3:

Input: queryIP = "256.256.256.256"
Output: "Neither"
Explanation: This is neither a IPv4 address nor a IPv6 address.
 

Constraints:

queryIP consists only of English letters, digits and the characters '.' and ':'.
*/

// follow the rules: implemented in one function for mixed detection of IPv4 or IPv6
lass Solution {
public:
    string validIPAddress(string queryIP) {
        bool checkIPv4 = false;
        bool checkIPv6 = false;
        bool leadingZero = false;        
        bool valid = true;
        int digits = 0;  // number of digits of a given token
        int tokens = 0;  // number of tokens
        int num = 0;  // decimal value
        for(int i=0,j=0; j<=queryIP.size(); ++j) {  // token in [i,j) range (include j==queryIP.size() for the last token)
            char c = j<queryIP.size() ? queryIP[j] : 'X';
            if(j==queryIP.size() || c=='.' || c==':') {  // end of a token
                if(c == '.')
                    checkIPv4 = true;
                else if(c == ':')
                    checkIPv6 = true;

                digits = j - i;
                if(!digits)  // must be detected here (as at the end of the loop the #digits might be zero when starting a new token, e.g., 192..1.1)
                    valid = false;
                if(checkIPv4 && (num>255 || (leadingZero&&digits>1)))  // leading zero must be detected at the end of a token (e.g., 192.0.0.1)
                    valid = false;      
                ++tokens;
                i = j + 1; // move to the starting point of next token
                num = 0;
                leadingZero = false;
            }
            else if(c>='0' && c<='9') {
                if(i==j && c=='0')
                    leadingZero = true;
                num = num*10 + c - '0';
            }
            else if(c>='a'&&c<='f' || c>='A'&&c<='F') {
                checkIPv6 = true;
            }
            else
                valid = false;

            // check legality
            if(checkIPv4 && checkIPv6)
                valid = false;
            else if(digits>4 || j-i+1>4/*the input may not have any ./: as separator*/)
                valid = false;
            else if(checkIPv4 && (num>255 || tokens>4))
                valid = false;
            else if(checkIPv6 && tokens>8)
                valid = false;

            if(!valid) {
                return "Neither";
            }
        }

        if(checkIPv4 && tokens==4)
            return "IPv4";
        else if(checkIPv6 && tokens==8)
            return "IPv6";
        else
            return "Neither";
    }
};
