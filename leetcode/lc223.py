class Solution(object):
    def digit_at(self, n, i):
        return (n%i - n%(i/10))/(i/10);
    
    def pow10(self, pow): #logarithmic (if generalize (chunks), then add 1 or not depending on if (100) or (200) -- everything else is same)
        ans = 0 #//don't take first digit into account
        #1s digits are number of tens
        #10s digits are number of hundreds * 10
        #100s digits are number of thousands * 100
        #last digit is 1
        i = 1
        while i < pow:
            ans += (pow/(i*10))*(i)
            i*=10
        
        return ans
    
    def countDigitOne(self, n):
        ans = 0
        i = 10 #start at ones place
        while(n%(i/10) < n):
            digit = self.digit_at(n, i)
            print(digit)
            ans += digit * self.pow10(i/10)
            if digit == 1:
                ans += 1
            
            if digit == 1:
                ans += n%(i/10)

            elif digit > 1:
                ans += i/10

            i*=10
        
        return ans
        
