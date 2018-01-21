import sys
import re
def Sort(ans):#Dealing the data
    a=0
    b = []
    c = []
    count = 0
    for i in range(0,len(ans),1):
        for j in range(0,len(ans[i])-1,1):
            for k in range(j+1,len(ans[i]),1):
                if ans[i][j] == ans[i][k]:
                    count += 1
            if count == 0:
                b.append(ans[i][j])
            count=0
        if len(ans[i])-1>=0:
            b.append(ans[i][len(ans[i])-1])
        c.append(b)
        b = []
    for k in range(0,len(c),1):
        for l in range(0,len(c[k]),1):
            if isinstance(c[k][l][0],float):
                if isinstance(c[k][l-1][0],str):
                    a=l-1
                    for h in range(l + 1, len(c[k]), 1):
                        if isinstance(c[k][h][0], str):
                            if h - a > 2:
                                b = []
                                for q in range(a + 1, h, 1):
                                    b.append(c[k][q])
                                if c[k][a][0] > c[k][h][0]:
                                    b.sort(reverse=True)
                                else:
                                    b.sort()
                                if c[k][a][1] > c[k][h][1]:
                                    b.sort(key=lambda x: x[1], reverse=1)
                                else:
                                    b.sort(key=lambda x: x[1])
                                t = 0
                                for q in range(a + 1, h, 1):
                                    c[k][q] = b[t]
                                    t += 1
                                break
                            else:
                                break
                else:
                    break
    return c
def IsNum(n):#Check if it is number or not
    try:
        float(n)
        return True
    except ValueError:
        pass

    try:
        import unicodedata
        unicodedata.numeric(n)
        return True
    except (TypeError, ValueError):
        pass

    return False
def CheckInput(ans):#check the format
    get = re.match(r'(.*?) (.*?) (.*)', ans, re.M | re.I)
    get2 = re.match(r'(.*?) "(.*?)" (.*)', ans, re.M | re.I)
    count = 0
    result = 1
    if get == None:
        print 'Error:Missing space!'
        result = 0
    elif get2 == None:
        print 'Error:Missing double quotation marks!'
        result = 0
    if ans[1] != ' ':
        print 'Error:Wrong instruction!'
        result = 0
    for i in range(1, len(ans), 1):
        if ans[i] != '(' and ans[i] != ')':
            i += 1
        else:
            if ans[i-1] != ' ' and ans[i] == '(':
                print 'Error:White-space must be in front of the first coordinate!'
                result = 0
            break
    if i >= len(ans):
        print 'Error:No bracket!'
        result = 0
    elif ans[i] == ')':
        print 'Error:Missing bracket!'
        result = 0
    else:
        for j in range(i, len(ans), 1):
            if ans[j] == '(':
                count += 1
                if count >= 2:
                    print 'Error:Missing bracket!'
                    result = 0
                    break
            elif ans[j] == ')':
                count -= 1
                if count < 0:
                    print 'Error:Missing bracket!'
                    result = 0
                    break
        if count == 1:
            print 'Error:Missing bracket!'
            result = 0
    return result
def CheckSameName(ans):
    k = 1
    for i in range(0,len(ans),1):
        for j in range(i+1,len(ans),1):
            if ans[i][0].lower() == ans[j][0].lower():
                print "Error:Same street name!"
                return 0
            elif len(ans[i]) == len(ans[j]):
                while k < len(ans[i]):
                    if ans[i][k] == ans[j][k]:
                        k += 1
                    else:
                        break
                if k >= len(ans[i]):
                    print "Error:Two different streets have the same coordinates!"
                    return 0
def FinalCheckSame(ans):
    Middle=[]
    Final=[]
    for i in range(0,len(ans),1):
        for j in range(0,len(ans[i])-1,1):
            Middle.append(ans[i][j])
            for k in range(j+1,len(ans[i]),1):
                if ans[i][j]==ans[i][k]:
                    Middle.pop()
                    break
        if len(ans[i]) > 1:
            Middle.append(ans[i][len(ans[i])-1])
        Final.append(Middle)
        Middle=[]
    return Final
def intersect (x1,y1,x2,y2,x3,y3,x4,y4):
    Coor = []
    Coor2=[]
    if x1 == x2 and x3 == x4:
        if x1 == x3:
            if min(y3,y4)>max(y1,y2) or max(y3,y4)<min(y1,y2):
                return
            elif min(y3,y4)==max(y1,y2):
                xcoor = x1
                ycoor=min(y3,y4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            elif max(y3,y4)==min(y1,y2):
                xcoor = x1
                ycoor=max(y3,y4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            else:
                xcoor = x1
                if y3==max(y1,y2,y3,y4)and y1==min(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y2
                elif y3==min(y1,y2,y3,y4)and y1==max(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y2
                elif y3==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y1
                elif y3==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y1
                elif y4==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y1
                elif y4==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y1
                elif y4==max(y1,y2,y3,y4)and y1==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y2
                elif y4==min(y1,y2,y3,y4)and y1==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y2
                elif y1==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y4
                elif y1==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y4
                elif y3==max(y1,y2,y3,y4)and y4==min(y1,y2,y3,y4):
                    ycoor1 = y1
                    ycoor2 = y2
                elif y3==min(y1,y2,y3,y4)and y4==max(y1,y2,y3,y4):
                    ycoor1 = y1
                    ycoor2 = y2
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor1, 2))
                Coor2.append(round(xcoor, 2))
                Coor2.append(round(ycoor2, 2))
                return [Coor,Coor2]
        else:
            return
    elif x3 == x4:
        xcoor = x3
        ynum = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)
        yden = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        ycoor = ynum / yden
        if ycoor >= min(y3, y4) and ycoor <= max(y3, y4) and xcoor <= max(x1,x2) and xcoor >= min(x1,x2):
            Coor.append(round(xcoor, 2))
            Coor.append(round(ycoor, 2))
            return Coor
        else:
            return
    elif x1 == x2:
        xcoor = x1
        ynum = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)
        yden = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)
        ycoor = ynum / yden
        if ycoor >= min(y1, y2) and ycoor <= max(y1, y2) and xcoor <= max(x3,x4) and xcoor >= min(x3,x4):
            Coor.append(round(xcoor, 2))
            Coor.append(round(ycoor, 2))
            return Coor
        else:
            return
    elif y1 == y2 and y3 == y4:
        if y1 == y3:
            if min(x3,x4)>max(x1,x2) or max(x3,x4)<min(x1,x2):
                return
            elif min(x3, x4) == max(x1, x2):
                ycoor = y1
                xcoor = min(x3, x4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            elif max(x3, x4) == min(x1, x2):
                ycoor = y1
                xcoor = max(x3, x4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            else:
                ycoor = y1
                if x3 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x2
                elif x3 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x2
                elif x3 == max(x1,x2,x3,x4) and x2 == min(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x1
                elif x3 == min(x1,x2,x3,x4) and x2 == max(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x1
                elif x4 == max(x1,x2,x3,x4) and x2 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x1
                elif x4 == min(x1,x2,x3,x4) and x2 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x1
                elif x4 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x2
                elif x4 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x2
                elif x2 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x4
                elif x2 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x4
                elif x3 == max(x1,x2,x3,x4) and x4 == min(x1,x2,x3,x4):
                    xcoor1 = x1
                    xcoor2 = x2
                elif x4 == max(x1,x2,x3,x4) and x3 == min(x1,x2,x3,x4):
                    xcoor1 = x1
                    xcoor2 = x2
                Coor.append(round(xcoor1, 2))
                Coor.append(round(ycoor, 2))
                Coor2.append(round(xcoor2, 2))
                Coor2.append(round(ycoor, 2))
                return [Coor, Coor2]
        else:
            return
    elif y3 == y4:
        ycoor = y3
        xnum = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
        xden = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
        xcoor = xnum / xden
        if xcoor >= min(x3, x4) and xcoor <= max(x3, x4) and ycoor <= max(y1,y2) and ycoor >= min(y1,y2):
            Coor.append(round(xcoor, 2))
            Coor.append(round(ycoor, 2))
            return Coor
        else:
            return
    elif y1 == y2:
        ycoor = y1
        xnum = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4))
        xden = ((x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4))
        xcoor = xnum / xden
        if xcoor >= min(x1, x2) and xcoor <= max(x1, x2) and ycoor>= min(y3,y4) and ycoor <= max(y3,y4):
            Coor.append(round(xcoor, 2))
            Coor.append(round(ycoor, 2))
            return Coor
        else:
            return
    elif ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)) == 0:
        if y3-y1 == ((y4-y3)*x3/(x4-x3))-((y2-y1)*x1/(x2-x1)):
            if min(x3,x4)>max(x1,x2) or max(x3,x4)<min(x1,x2):
                return
            elif min(y3, y4) == max(y1, y2):
                if min(x1,x2)==max(x3,x4):
                    xcoor = min(x1,x2)
                elif max(x1,x2)==min(x3,x4):
                    xcoor=max(x1,x2)
                ycoor = min(y3, y4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            elif max(y3, y4) == min(y1, y2):
                if min(x1,x2)==max(x3,x4):
                    xcoor = min(x1,x2)
                elif max(x1,x2)==min(x3,x4):
                    xcoor=max(x1,x2)
                ycoor = max(y3, y4)
                Coor.append(round(xcoor, 2))
                Coor.append(round(ycoor, 2))
                return Coor
            else:
                if y3==max(y1,y2,y3,y4)and y1==min(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y2
                elif y3==min(y1,y2,y3,y4)and y1==max(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y2
                elif y3==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y1
                elif y3==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y4
                    ycoor2 = y1
                elif y4==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y1
                elif y4==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y1
                elif y4==max(y1,y2,y3,y4)and y1==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y2
                elif y4==min(y1,y2,y3,y4)and y1==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y2
                elif y1==min(y1,y2,y3,y4)and y2==max(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y4
                elif y1==max(y1,y2,y3,y4)and y2==min(y1,y2,y3,y4):
                    ycoor1 = y3
                    ycoor2 = y4
                elif y3==max(y1,y2,y3,y4)and y4==min(y1,y2,y3,y4):
                    ycoor1 = y1
                    ycoor2 = y2
                elif y3==min(y1,y2,y3,y4)and y4==max(y1,y2,y3,y4):
                    ycoor1 = y1
                    ycoor2 = y2
                if x3 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x2
                elif x3 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x2
                elif x3 == max(x1,x2,x3,x4) and x2 == min(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x1
                elif x3 == min(x1,x2,x3,x4) and x2 == max(x1,x2,x3,x4):
                    xcoor1 = x4
                    xcoor2 = x1
                elif x4 == max(x1,x2,x3,x4) and x2 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x1
                elif x4 == min(x1,x2,x3,x4) and x2 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x1
                elif x4 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x2
                elif x4 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x2
                elif x2 == min(x1,x2,x3,x4) and x1 == max(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x4
                elif x2 == max(x1,x2,x3,x4) and x1 == min(x1,x2,x3,x4):
                    xcoor1 = x3
                    xcoor2 = x4
                elif x3 == max(x1,x2,x3,x4) and x4 == min(x1,x2,x3,x4):
                    xcoor1 = x1
                    xcoor2 = x2
                elif x4 == max(x1,x2,x3,x4) and x3 == min(x1,x2,x3,x4):
                    xcoor1 = x1
                    xcoor2 = x2
                if ((y1-y2)/(x1-x2))>0:
                    Coor.append(round(max(xcoor1,xcoor2), 2))
                    Coor.append(round(max(ycoor1,ycoor2), 2))
                    Coor2.append(round(min(xcoor1,xcoor2), 2))
                    Coor2.append(round(min(ycoor1,ycoor2), 2))
                elif ((y1-y2)/(x1-x2))<0:
                    Coor.append(round(max(xcoor1, xcoor2), 2))
                    Coor.append(round(min(ycoor1, ycoor2), 2))
                    Coor2.append(round(min(xcoor1, xcoor2), 2))
                    Coor2.append(round(max(ycoor1, ycoor2), 2))
                return [Coor, Coor2]
        else:
            return
    else:
        xnum = ((x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4-y3*x4))
        xden = ((x1-x2)*(y3-y4) - (y1-y2)*(x3-x4))
        xcoor =  xnum / xden
        ynum = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4-y3*x4)
        yden = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4)
        ycoor = ynum / yden
        if xcoor >= min(x1, x2) and xcoor <= max(x1, x2) and xcoor >= min(x3, x4) and xcoor <= max(x3, x4) and ycoor >= min(
            y1, y2) and ycoor <= max(y1, y2) and ycoor >= min(y3, y4) and ycoor <= max(y3, y4):
            Coor.append(round(xcoor, 2))
            Coor.append(round(ycoor, 2))
            return Coor
def divide(ans):
    line = []
    line2 = []
    for i in range(0, len(ans), 1):
        for j in range(1, len(ans[i])-1, 1):
            line.append(ans[i][j])
            line.append(ans[i][j+1])
        line2.append(line)
        line = []
    return line2
def Calculate(ans):
    Ins = []
    g1 = []
    Final=[]
    twice=ans
    if len(ans) > 1:
        for t in range(0, len(ans), 1):
            twice.append(ans[t])
        for i in range(0, len(twice)/2, 1):
            for j in range(0, len(twice[i]) - 1, 2):
                x1 = float(twice[i][j][0])
                y1 = float(twice[i][j][1])
                x2 = float(twice[i][j + 1][0])
                y2 = float(twice[i][j + 1][1])
                g1.append(twice[i][j])
                g1.append(twice[i][j + 1])
                count = 0
                count2 = 0
                for h in range(i + 1, i+(len(twice)/2), 1):
                    for k in range(0, len(twice[h]) - 1, 2):
                        x3 = float(twice[h][k][0])
                        y3 = float(twice[h][k][1])
                        x4 = float(twice[h][k + 1][0])
                        y4 = float(twice[h][k + 1][1])
                        count += 1
                        Ins = intersect(x1,y1,x2,y2,x3,y3,x4,y4)
                        if Ins != None:
                            g1.pop()
                            if isinstance(Ins[0],float)==0:
                                g1.append(Ins[0])
                                g1.append(Ins[1])
                            else:
                                g1.append(Ins)
                            g1.append(ans[i][j + 1])
                        elif Ins == None:
                            count2 += 1
                        Ins = []
                if len(twice) > 1 and h == (i+(len(twice)/2)-1) and k == (len(twice[h]) - 2) and count2 >= count:
                    g1.pop()
                    g1.pop()
            Final.append(g1)
            g1 = []
    return Sort(Final)
def a(ans):#check the content and process the data
    SN = []
    IP = []
    CO = []
    NU = []
    NU2 = []
    Pair = []
    count = 0
    count2 = 0
    One = []
    for i in range(0,len(ans),1):
        if ans[i] == '(' or ans[i] == ')':
            count += 1
        elif ans[i] == ',':
            count2 += 1
            if count2 < (count+1)/2:
                print 'Error:Missing comma in coordinate!'
                return
            elif count2 > (count+1)/2:
                print 'Error:Comma out of coordinate!'
                return
    for i in range(3,len(ans),1):
        if ans[i] != '"':
            if ans[i].isspace() or ans[i].isalpha():
                SN.append(ans[i])
            else:
                print "Error:Alphabetical and space characters in street name only!"
                return
        else:
            IP.append(''.join(SN))
            break
    while i<len(ans):
        if IsNum(ans[i])or ans[i]=='-':
            NU.append(ans[i])
        elif ans[i] == ',' or ans[i] == ')':
            if len(NU) > 0:
                NU2.append(''.join(NU))
                Pair.append(''.join(NU))
                NU = []
                if len(NU2)%2 == 0:
                    CO.append(NU2)
                    NU2 = []
        i += 1
    for k in range(0,len(CO)-1,1):
        if CO[k] == CO[k+1]:
            print "Error:Duplicate coordinate!"
            return
    if len(Pair) == 0:
        print 'Error:Wrong coordinate(must be number)!'
    elif count2 != (count/2):
        print 'Error:Missing comma!'
    elif len(CO) == 1:
        print 'Error:A street must be more than two coordinates!'
    elif len(Pair)%2 == 1:
        print 'Error:Wrong coordinate(the coordinate must be in pair)!'
    elif len(CO)*2 > count:
        print 'Error:Missing bracket!'
    else:
        return IP+CO
def r(ans,g):
    if ans[1] != ' ':
        print 'Error:Wrong instruction!'
        return 1
    a=[]
    b=[]
    count=len(g)
    if len(g)>0:
        j=3
        while ans[j]!='"':
            j+=1
        for i in range(3,j,1):
            a.append(ans[i])
        b.append(''.join(a))
        if len(b)==0:
            print "Error:Please give me a street name!"
            return 1
        for k in range(0,len(g),1):
            if g[k][0]==b[0]:
                g.pop(k)
                break
        if len(g)==count:
            print "Error:No this street!"
            return 1
    else:
        print "Error:No street!"
        return 1
def StrtoFlo(ans):
    fi=[]
    mi = []
    ins=[]
    for i in range(0,len(ans),1):
        for j in range(0,len(ans[i]),1):
            mi.append(round(float(ans[i][j][0]),2))
            mi.append(round(float(ans[i][j][1]),2))
            fi.append(mi)
            mi=[]
        ins.append(fi)
        fi=[]
    return ins
def ProcessGraph(ans):
    a=[]
    b=[]
    c=[]
    d=[]
    Middle = []
    for i in range(0,len(ans),1):
        for j in range(0,len(ans[i]),1):
            a.append(ans[i][j])
    if len(a)>0:
        for k in range(0,len(a)-1,1):
            b.append(a[k])
            for h in range(k+1,len(a),1):
                if a[k]==a[h]:
                    b.pop()
                    break
        b.append(a[len(a)-1])
        print "V={"
        for l in range(0,len(b),1):
            print " %d: (%.2f,%.2f)"%(l+1,b[l][0],b[l][1])
        print "}"
        print "E={"
        for x in range(0, len(ans), 1):
            for y in range(0, len(ans[x])-1, 1):
                for z in range(0, len(b), 1):
                    if ans[x][y] == b[z]:
                        s=z
                    if ans[x][y+1]==b[z]:
                        t=z
                c.append(s+1)
                c.append(t+1)
                d.append(c)
                c=[]
        for q in range(0, len(d)-1, 1):
            Middle.append(d[q])
            for w in range(q + 1, len(d), 1):
                if d[q] == d[w]:
                    Middle.pop()
                    break
                elif d[q][0] == d[w][1] and d[q][1] == d[w][0]:
                    Middle.pop()
                    break
        if len(d) > 1:
            Middle.append(d[len(d) - 1])
        if len(Middle)>0:
            for e in range(0,len(Middle),1):
                print " <%d,%d>"%(Middle[e][0],Middle[e][1])
        print "}"
    return b
def main():
    g = []
    aaaa=[]
    while True:
        #print 'If you want to add a street, type "a "Street name" (x1,y1)(x2,y2)...(xn,yn)"'
        #print 'If you want to change the specification of a street, type c'
        #print 'If you want to remove a street, type r'
        #print 'If you want to output the corresponding graph, type g'
        #print 'If you want to quit, type q'
        ans = sys.stdin.readline().strip('\n')
        if ans == '':
            continue
        elif ans[0] == 'a' and len(ans)>1:
            if CheckInput(ans) == 1:
                aa = a(ans)
                if aa != None:
                    g.append(aa)
                if CheckSameName(g) == 0:
                    g.pop()
                aaa = divide(g)
                aaaa = Calculate(aaa)
        elif ans[0] == 'c' and len(ans)>1:
            if len(g)>0:
                if CheckInput(ans) == 1:
                    if r(ans, g)!=1:
                        aa = a(ans)
                        if aa != None:
                            g.append(aa)
                        if CheckSameName(g) == 0:
                            g.pop()
                        aaa = divide(g)
                        aaaa = Calculate(aaa)
            else:
                print 'Error:No street!'
        elif ans[0] == 'r' and len(ans)>1:
            get = re.match(r'(.*?) (.*?)', ans, re.M | re.I)
            get2 = re.match(r'(.*?) "(.*?)"', ans, re.M | re.I)
            result = 1
            if get == None:
                print 'Error:Missing space!'
                result = 0
            elif get2 == None:
                print 'Error:Missing double quotation marks!'
                result = 0
            if r(ans,g)!=1 and result != 0:
                aaa = divide(g)
                aaaa = Calculate(aaa)
        elif ans == 'g' :
            a3=[]
            a4=[]
            for i in range(0,len(aaaa),1):
                for j in range(1,len(aaaa[i]),1):
                    if j==1:
                        a3.append(aaaa[i][0])
                    a3.append(aaaa[i][j])
                    if isinstance(aaaa[i][j][0],str):
                            if j<len(aaaa[i])-1:
                                if isinstance(aaaa[i][j+1][0],str):
                                    a4.append(a3)
                                    a3=[]
                            elif j == len(aaaa[i])-1:
                                a4.append(a3)
                                a3 = []
            a5 = StrtoFlo(a4)
            a6 = FinalCheckSame(a5)
            if len(a6)>0 :
                ProcessGraph(a6)
            else:
                print "V={"
                print "}"
                print "E={"
                print "}"
        else:
            print 'Error:The instruction doesn\'t exist'
    sys.exit(0)
if __name__ == '__main__':
    main()
