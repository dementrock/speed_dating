# coding = utf-8
import codecs
raw_file = codecs.open("data.tsv", "r", "utf-8")
file_content = raw_file.read()

rows = [row for row in file_content.split('\n')]
words_in_row = [[word for word in row.split('\t')] for row in rows]
words_in_row = words_in_row[:-1]

cnt_options = len(words_in_row[0])
cnt_people = len(words_in_row)
words_in_columns = [[row[i] for row in words_in_row] for i in range(0, cnt_options)]

choiceset = [[] for i in range(0, cnt_options)]
cntchoice = [0 for i in range(0, cnt_options)]
choice = [[0 for j in range(0, cnt_options)] for i in range(0, cnt_people)] 

#print(words_in_columns[8])

for i in range(0, len(words_in_columns)):
    column = words_in_columns[i]
    #print(i, column)
    if i == 8: # Special processor
        hobbyset = []
        cnthobby = 0
        for j in range(0, len(column)):
            choice[j][i] = []
            words = column[j]
            for word in words.split(", "):
                if word not in hobbyset:
                    hobbyset += [word]
                pos = 0
                for k in range(0, len(hobbyset)):
                    if hobbyset[k] == word:
                        pos = k + 1
                        break
                choice[j][i] += [pos]
            choice[j][i] = sorted(choice[j][i])
    else:
        for j in range(0, len(column)):
            word = column[j]
            if word == "empty":
                choice[j][i] = 0
                continue
            if word not in choiceset[i]:
                choiceset[i] += [word]
            pos = -1 
            for k in range(0, len(choiceset[i])):
                if word == choiceset[i][k]:
                    pos = k
                    break
            choice[j][i] = pos + 1
        """else:
            choiceset[i] += word
            choice[j][i] = len(choiceset[i])
            cntchoice[i] += 1
            choice[j][i] = choicedict[i][word] = cntchoice[i]"""

"""for i in range(0, cnt_people):
    choice[i] =  [choice[i][4]] + choice[i][6:8] + choice[i][9:] + [choice[i][8]]
    output = ""
    for j in range(0, len(choice[i]) - 1):
        output += str(choice[i][j]) + " "
    print(output)
    output = str(len(choice[i][-1])) + " "
    for j in range(0, len(choice[i][-1])):
        output += str(choice[i][-1][j]) + " "
    print(output)"""

"""
    for j in range(0, len(choice[i])):
        print(choiceset[j][choice[i][j] - 1],choice[i][j])"""

#for i in range(0, len(choiceset[6])):
#    print(i + 1, choiceset[6][i])

"""for i in range(0, len(choiceset[1])):
    print(i + 1)
    print(choiceset[1][i])
    print(choiceset[3][i])"""

raw_file = open("plan.txt", "r")
content = raw_file.read()
for row in content.split('\n'):
    if row:
        a, b = row.split(' ')
        a, b = int(a), int(b)
        print (a, choiceset[1][a - 1],"&", b, choiceset[1][b - 1])
        print (choiceset[3][a - 1], choiceset[3][b - 1])
        print ()
    #print(row)

#for i in range


#print(choiceset)

#for column in words_in_columns:
#    print('---:')
#    for word in column:
#        print( word)
#    print('end')
#for 
