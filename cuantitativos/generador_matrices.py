with open('200_out0.', 'w') as f:
    for x in range(1,201):
        for y in range(x,201):
            if x != y :
                f.write(str(x))
                f.write(" ")
                f.write(str(y))
                f.write('\n')