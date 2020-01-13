from random import seed
from random import randint

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

def modExp(a, b, n):
    #print("a: "+str(a)+ " b: "+str(b))
    return (a**b) %n

def witness(a, n):
    t = 1
    while((n-1)%(2**(t+1))==0):
        t += 1
    u = int((n-1)/(2**t))
    x = modExp(a, u, n)
    for i in range(1, t+1):
        xb = x
        x = (x*x) % n
        if x==1 and xb != 1 and xb != n-1:
            return True
    if x != 1:
        return True
    return False

def MillRab(n, s):
    for j in range(1, s+1):
        a = randint(1, n-1)
        if witness(a, n):
            return False
    return True

def randPrime():
    a = randint(100, 200)
    if a%2 ==0:
        a +=1
    while( not MillRab(a, 10)):
        a +=2
    return a

#p = randPrime()
#q = randPrime()

def RSA():
    #p = 17
    #q = 19
    p = randPrime()
    q = randPrime()
    print("P: "+str(p)+" Q: "+str(q))

    n = p * q
    pi = phi(p, q)
    e = findE(pi)
    #print("e:", e)
    d = findD(e, pi)

    return e, n, d, n

#main

(e, n, d, n) = RSA()

M = 1000

print("Public Key(e,n): (", e, ",", n,")")
print("Private Key(d,n): (", d,",", n,")")
print("M:", M)

P = (M**e)%n
print("Crypted Message:", P)
S = (P**d)%n
print("Decrypted Message:", S)

