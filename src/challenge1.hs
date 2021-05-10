-- Compiled using GHC 8.10.4
-- Tested on x86 macOS 11.3.1
--
-- Due to the use of interact, the input must be piped into the compiled binary
-- For Example:
--    `echo 'HelloWorld' | ./challenge1`
-- or:
--    `./challenge1 < input.txt`


solve :: String -> String
solve str = rev str ++ "\n"


-- I didn't wanna just straight up use the build in `reverse` function from Haskell
--  so here's a recursive implementation
rev :: String -> String
rev ""  = ""
rev str = rev (tail str) ++ [head str]


main = interact solve

