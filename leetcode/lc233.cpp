class Solution {
private:
    unsigned long digit_at(const unsigned long &n, const unsigned long &i){
        return (n%i - n%(i/10))/(i/10);
    }
    unsigned long pow10(const unsigned long &pow){ //logarithmic (if generalize (chunks), then add 1 or not depending on if (100) or (200) -- everything else is same)
        unsigned long ans = 0; //don't take first digit into account
        //1s digits are number of tens
        //10s digits are number of hundreds * 10
        //100s digits are number of thousands * 100
        //last digit is 1
        for(unsigned long i = 1; i < pow; i*=10){
            ans += (pow/(i*10))*(i);
        }
        return ans;
    }
public:
    int countDigitOne(unsigned long n) { //WHATS THE POINT IF THE NUMBER DOESN'T EVEN FIT I MEAN I GET THAT IT HAS TO BE BIG BUT ITS AN INT
        unsigned long ans = 0;
        unsigned long i = 10; //start at ones place
        while(n%(i/10) < n){
            unsigned long digit = digit_at(n, i);
            cout << digit << endl;
            ans += digit * pow10(i/10);
            if(digit == 1){
                ++ans;
            }
            if(digit == 1){
                ans += n%(i/10);
            }
            else if(digit > 1){
                ans += i/10;
            }
            i*=10;
        }
        return ans;
    }
};
