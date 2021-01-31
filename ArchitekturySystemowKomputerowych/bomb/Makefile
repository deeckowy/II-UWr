BOMBNAME = $(shell basename `pwd`)

PHASE1 = "Phase 1 defused. How about the next one?"
PHASE2 = "That's number 2.  Keep going!"
PHASE3 = "Halfway there!"
PHASE4 = "So you got that one.  Try this one."
PHASE5 = "Good work!  On to the next..."
PHASE6 = "Congratulations! You've defused the bomb!"
PHASE7 = "Wow! You've defused the secret stage!"

all: test-1 test-2 test-3 test-4 test-5 test-6 test-7

bomb:
	cp -v /root/bombs/$(BOMBNAME)/* .

test-%: bomb
	@echo -n "PHASE $*... "
	@cat solution.txt | ./bomb | grep --quiet $(PHASE$*) \
		|| (echo "failed" && exit 1)
	@echo "passed"
