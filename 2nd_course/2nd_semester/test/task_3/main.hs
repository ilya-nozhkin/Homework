rowLength :: Integer -> Integer -> Integer
rowLength a n = a - abs (n - a)

getRow :: Integer -> Integer -> String
getRow a n = getRow' (l * 2 - 1) (a - l) "" where
    l = rowLength a n
    getRow' 0 0 r = r
    getRow' 0 s r = getRow' 0 (s - 1) (' ':r)
    getRow' x s r = getRow' (x - 1) s ('x':r)

printDiamond :: Integer -> IO()
printDiamond 0 = return ()
printDiamond a = printDiamond' a (a * 2 - 1) where
    printDiamond' a 0 = return ()
    printDiamond' a l = 
        putStrLn (id (getRow a l)) >>
        printDiamond' a (l - 1)
