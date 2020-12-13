class Solution(object):
    def valid(self, tLets, curLets):
        for i in tLets:
            if i not in curLets or curLets[i] < tLets[i]:
                return False
        return True
    def minWindow(self, s, t):
        tLets = {}
        for i in t:
            if i in tLets:
                tLets[i] += 1
            else:
                tLets[i] = 1
        start, end = 0, 0
        curLets = {}
        ans = ""
        while start < len(s) and end <= len(s):
            if self.valid(tLets, curLets):
                if ans == "" or end - start < len(ans):
                    ans = s[start:end]
                curLets[s[start]] -= 1 
                start += 1
            else:
                try:
                    if s[end] in curLets:
                        curLets[s[end]] += 1
                    else:
                        curLets[s[end]] = 1
                except:
                    break
                end += 1
        return ans
                    
        
        
