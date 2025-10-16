test1 = [1,2,3,4,5]
test2 = [2,1,5,0,4,6]

def increasingTriplet(nums: list[int]) -> bool:

    if len(nums) < 3:
        return False

    numsDict = dict(enumerate(nums))

    sortedArr = list(map(lambda x: x[0], sorted(numsDict.items(), key=lambda x: x[1])))

    print(sortedArr)

    for i in range(2, len(sortedArr)):
        if sortedArr[i - 2] < sortedArr[i - 1] and sortedArr[i - 1 ] < sortedArr[i]:
            return True
    
    return False

print(increasingTriplet(test1))
print(increasingTriplet(test2))