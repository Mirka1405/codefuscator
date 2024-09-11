# codefuscator
Do you want your friends to look at your code but prevent them from stealing it? No? Well guess what I got one anyway

# How to use
Download the exe from releases, then open cmd; I'm sure you know how to do that.

Arguments: codefuscator <input file> <output file> <options>  
options may contain any combination of the following:  
g - replace semicolons with greek question marks  
z - randomly place ZWSP characters  
c - turn compatible latin letters into cyrillic  
After an option write a number to set the probability (0 to 1, default: 0.3)  
Possible syntax: codefuscator in.txt out.txt g0.5 c1  

# What exactly does it do
If you have greek question mark option selected, it may replace a semicolon with a greek question mark (side-by-side comparison: ;; can you tell which is which?). Have you seen that meme on r/ProgrammerHumor where you replace your JS developer friend's semicolons with ;? That was actually the inspiration for the entire tool.  
If you have cyrillification option selected, if a character is in the list of compatible characters (aAeEToOxXyKHcCM) it may be replaced with a cyrillic character.  
If you have zero-width-space option selected, a ZWSP may be placed before any character. This is the most powerful option because you cannot see the issue (if your editor doesn't show the special characters), and the program is able to work with unicode characters so do not worry about your unicode being disrupted.

# Why
Because.
