# Complex-prime-numbers
A generator of prime numbers in complex

This program generates prime numbers in complex numbers. It's like prime nubers in normal numbers, but they are x + yi, where x and y are normal numbers.

It has text output, a list of all found prime numbers and then a map, where the number is 10 * (y % 10) + x % 10, the numbers on the x-axis are (x % 1000) / 10 and the numbers on y-axis are (y % 1000) / 10. Each prime number is marked by ":." instead.

To generate a visual map put the text map onto a bitmap and use brightness and blur tools to highlight the structures.

0 + 1i is a prime number too, so all numbers those are not in the first quadrant can't be prime numbers, so only one quadrant is considered.

![Prime numbers in complex, range 0 - 200](https://github.com/Hume2/Complex-prime-numbers/blob/d7d917ba81f1e9a07f7f575b7edd9b410b515863/numbers_0_199.png?raw=true)
