from concurrent.futures import ThreadPoolExecutor
import time

def quicksort(a):
    if len(a)<=1:
        return a

    p=a[len(a)//2]

    l=[x for x in a if x<p]
    m=[x for x in a if x==p]
    r=[x for x in a if x>p]

    return quicksort(l)+m+quicksort(r)

n=int(input("Enter number of elements: "))

a=list(map(int,input("Enter elements: ").split()))

print("\nOriginal Array:")
print(a)

s=time.time()

with ThreadPoolExecutor() as ex:
    result=ex.submit(quicksort,a).result()

e=time.time()

print("\nSorted Array:")
print(result)

print("\nExecution Time:",e-s)
