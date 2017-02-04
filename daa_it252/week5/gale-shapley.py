#!/usr/bin/env python

from sys import argv

def match(men, women, f):
    men_prefs = {}
    men_status = {}
    for man in men:
        # men_prefs[man] = list(raw_input("Enter prefs of " + man + " : ").split())
        men_prefs[man] = list(f.readline().replace('\n','').split())
        men_status[man] = "FREE"

    women_prefs = {}
    women_status = {}
    for woman in women:
        # women_prefs[woman] = list(raw_input("Enter prefs of " + woman + " : ").split())
        women_prefs[woman] = list(f.readline().replace('\n','').split())
        women_status[woman] = "FREE"

    while "FREE" in men_status.values():
        man = men_status.keys()[men_status.values().index("FREE")]
        woman = men_prefs[man].pop(0)
        if women_status[woman] == "FREE":
            men_status[man] = woman
            women_status[woman] = man
        else:
            m1 = women_status[woman]
            if women_prefs[woman].index(man) < women_prefs[woman].index(m1):
                women_status[woman] = m1
                men_status[man] = woman
                men_status[m1] = "FREE"
            else:
                continue

    matches = []
    for man in men_status:
        matches.append([man, men_status[man]])
    return matches

def main():
    # men = list(raw_input("Enter men: ").split())
    # women = list(raw_input("Enter women: ").split())
    f = open(argv[1], 'r')
    men = list(f.readline().replace('\n','').split())
    women = list(f.readline().replace('\n','').split())
    matches = match(men, women, f)
    for couple in matches:
        print couple[0], " matches ", couple[1]
    f.close()

if __name__ == '__main__':
    main()
