def randPrime():
    print("hi")

def extEuclid(a, b):
    if b==0:
        return a, 1, 0
    else:
        (d, x, y) = extEuclid(b, a % b)
        d, x, y = d, y, x - (a//b)* y
        return d, x, y

def phi(p, q):
    return (p-1)*(q-1)

def findE(pi):
    i = 3
    (d,_,_) = extEuclid(i, pi)
    while d!=1:
        i+= 2
        (d,_,_) = extEuclid(i, pi)
    return i

def findD(e, n):
    print(str(e)+" "+ str(n))
    (d, x, y) = extEuclid(e, n)
    return x % n


#p = randPrime()
#q = randPrime()

def RSA():
    p = 17
    q = 19

    n = p * q
    pi = phi(p, q)
    e = findE(pi)
    print("e:", e)
    d = findD(e, pi)

    return e, n, d, n

#main

(e, n, d, n) = RSA()

M = 53

print("Public Key(e,n): (", e, ",", n,")")
print("Private Key(d,n): (", d,",", n,")")
print("M:", M)

P = (M**e)%n
print("Crypted Message:", P)
S = (P**d)%n
print("Decrypted Message:", S)

