#!/bin/csh



printf "testing /reset/\n"
python3 test_reset.py

printf "\ntesting /colleges/\n"
python3 test_colleges.py

printf "\ntesting /act/\n"
python3 test_act.py

printf "\ntesting /city/\n"
python3 test_city.py

printf "\ntesting /cost/\n"
python3 test_cost.py

printf "testing /pop/\n"
python3 test_pop.py

printf "\ntesting /region/\n"
python3 test_region.py

printf "\ntesting /sat/\n"
python3 test_sat.py

printf "\ntesting /state/\n"
python3 test_state.py
