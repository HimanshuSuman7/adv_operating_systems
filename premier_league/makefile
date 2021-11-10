# print_match_preview
# print_final_score
# get_rand_goals
# premier_league_board
# simulate_match
# check_conflict
# main
# project.h

result.out: main.c parent.o simulate_match.o
	gcc main.c parent.o simulate_match.o -o result.out

parent.o: parent.c project.h
	gcc -c parent.c

simulate_match.o: simulate_match.c project.h
	gcc -c simulate_match.c

clean:
	rm -f *.o *.out