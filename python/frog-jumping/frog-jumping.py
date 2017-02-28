#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys;
import os;
import copy;

reload(sys);
sys.setdefaultencoding("utf-8");



# inspired from https://www.youtube.com/watch?v=X3HDnrehyDM (Numberphile's "Frog Jumping" video, released on Feb 23th 2017). Change the initial field in line 135.
FROG = 0;
QUEEN = 1;
LAZYTOAD = 2;



def getPossibilities(currField):																					# get a field's possibilities by following the rule that a stack of frogs can only jump as far as it's high and cannot jump onto an empty place
	currPossibleMoves = [];
	for idx, val in enumerate(currField):
		
		if len(val) == 0:																							# only existing piles of frogs can jump
			continue
		if currField[idx][0] == LAZYTOAD:																			# piles which have a lazy toad at the bottom cannot jump
			continue;
			
		# jump left or right
		for jumpDist in [-len(val), len(val)]:
			if idx+jumpDist < 0  or  idx+jumpDist > len(currField)-1:												# do not jump out of the field
				continue;
			if len(currField[idx+jumpDist]) == 0:																	# do not jump onto blank spots
				continue;
			if currField[idx+jumpDist][-1] == QUEEN:																# do not jump onto spots where a queen is, because it always has to be on the top
				continue;
			
			# construct the new field
			newField = copy.deepcopy(currField);
			newField[idx+jumpDist].extend(val);
			newField[idx] = [];
			currPossibleMoves.append(newField);
			
	return currPossibleMoves;

def accept(currField):																								# if the field only contains a single stack with all the frogs, it is a final solution
	onlyOneStack = False;
	for val in currField:
		if len(val) > 0:
			if onlyOneStack:
				return False;
			onlyOneStack = True;
	return True;

deadEndFields = [];
deadEndFieldsUsed = 0;
def reject(currField, possibilities):
	global deadEndFieldsUsed;
	
	if len(possibilities) == 0:																						# if there are no more possible moves for this field, it is rejected
		return True;
	if str(currField) in deadEndFields:																				# if the current field is guaranteed to be a dead end (because it has been checked by the backtracking algorithm already), reject it as well
		deadEndFieldsUsed += 1;
		return True;
	return False;



numBacktracks = 0;
def backtrackField(rootField):																						# this recursive backtracking algorithm is more or less taken from https://en.wikipedia.org/wiki/Backtracking#Pseudocode
	global deadEndFields;
	global numBacktracks;
	numBacktracks += 1;
	
	if accept(rootField):
		return [rootField];
	possibilities = getPossibilities(rootField);
	if reject(rootField, possibilities):
		return False;
	
	for s in possibilities:
		result = backtrackField(s);
		if type(result) is list:																					# when this function returns a list, a solution was found in that call. Because we want to eventually return the solution, append the current field here
			ret = [rootField];
			ret.extend(result);
			return ret;
	
	for s in [str(rootField), str(rootField[::-1])]:																# when this code is reached, all previous calls to 'backtraceField' returned 'False'. In this case, it is sure to say that the current field ends only in dead ends. Save this information for later (efficiency purposes). As fields may be symmetrical, the right-to-left reversed version becomes a certain dead end as well.
		if s not in deadEndFields:
			deadEndFields.append(s);



def compactFormatField(currField):
	ret = "";
	for idx, val in enumerate(currField):
		ret += str(len(val));
		if len(val) != 0:
			if val[0] == LAZYTOAD:
				ret += " withLazyToad";
			if val[-1] == QUEEN:
				ret += " withQueen";
		if idx != len(currField)-1:
			ret += ",";
	return ret;

def prettyPrintField(currField, intro, introLine):
	maxHeight = len(max(currField, key=len))
	for y in range(maxHeight):
		
		# make it possible to set an introduction line before the "image"
		if y == introLine:
			sys.stdout.write(intro);
		else:
			sys.stdout.write(" " * len(intro));
		
		# draw the current row
		for x in currField:
			currIndex = maxHeight - y - 1;
			if currIndex >= len(x):
				sys.stdout.write("   ");
			else:
				if x[currIndex] == FROG:
					sys.stdout.write("🐸  ");
				elif x[currIndex] == QUEEN:
					sys.stdout.write("👑  ");
				elif x[currIndex] == LAZYTOAD:
					sys.stdout.write("😴  ");
		sys.stdout.write("\n");
	sys.stdout.write(" "*len(intro) + "▀"*(len(currField)*3) + "\n\n\n");
	sys.stdout.flush();
	

# the individual piles are defined from bottom to top, i.e. a lazy toad (id 2) always has to be at index [0] and a queen (id 1) always at index [-1] (the end of the array)
solution = backtrackField([[FROG], [], [FROG], [FROG], [FROG], [FROG], [FROG, FROG], [FROG], [FROG], [FROG, FROG, QUEEN], [LAZYTOAD]]);
if solution == None:
	print "No solution!"
else:
	for idx, val in enumerate(solution):
		prettyPrintField(val, "Step " + str(idx) + "    ", 0);

# print str(deadEndFieldsUsed) + " times dead end fields reused.";
# print str(numBacktracks) + " backtracks needed.";



