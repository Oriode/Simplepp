


namespace Regex {


	template<typename T>
	bool match( const BasicString<T> & str, const BasicString<T> & regExp ) {
		typedef struct stackItem {
			BasicString<T>::RandomAccessIterator strIt;
			BasicString<T>::RandomAccessIterator regIt;
			unsigned int actualIteration;
		} StackItem;

		//init the explicit stack.
		Vector<StackItem> stack;
		stack.reserve( 20 );

		//stack.clear();

		//Init the stack and the current position.
		StackItem currentItem = { str.getBegin(), regExp.getBegin(), 0 };
		stack.push( currentItem );

		//Init this bool because the management of bracket is a bit different.
		bool insideBracket = false;


		//Now check if we have the FORCE BEGIN char.
		bool forceBeginStr;
		if ( *currentItem.regIt == T( '^' ) ) {
			forceBeginStr = true;
			currentItem.regIt++;
			if ( currentItem.regIt == regExp.getEnd() )
				return true;
		} else
			forceBeginStr = false;



		//Now Start the loop.
		while ( true ) {
			//log(String(*currentItem.regIt) + " " + *currentItem.strIt );



			if ( insideBracket ) {
				if ( *currentItem.regIt == T( '\\' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					goto insideBracketLabel;
				} else if ( *currentItem.regIt == T( ']' ) ) {		//If we are closing the bracket.
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;

					if ( *currentItem.regIt == T( '+' ) || *currentItem.regIt == T( '*' ) ) {
						currentItem.regIt = stack.getLast().regIt;
						stack.getLast().strIt = currentItem.strIt;
						stack.getLast().actualIteration++;
					} else {
						stack.pop();
						insideBracket = false;
					}
				} else {
insideBracketLabel:
					if ( currentItem.strIt == str.getEnd() )		//if the string is finished, error anyway
						goto noMatchBracket;
					//We are inside a bracket, test are a bit tricky
					if ( *currentItem.regIt == T( '^' ) ) {	//If the first character is a NO
						currentItem.regIt++;
						while ( currentItem.regIt != regExp.getEnd() ) {
							if ( *currentItem.regIt == T( '\\' ) ) {
								currentItem.regIt++;
								if ( currentItem.regIt == regExp.getEnd() )
									return true;
								goto backetNoNormalChar;
							} else if ( *currentItem.regIt == T( '-' ) && currentItem.regIt + 1 != regExp.getEnd() && ( *( currentItem.regIt - 1 ) < *currentItem.strIt && *( currentItem.regIt + 1 ) > *currentItem.strIt ) ) {
								goto noMatchBracket;
							} else if ( *currentItem.regIt == T( ']' ) ) {
								currentItem.strIt++;
								goto bracketSuccess;
							} else backetNoNormalChar: if ( *currentItem.strIt == *currentItem.regIt ) {
								insideBracket = false;
								goto noMatchBracket;
							} else {
								currentItem.regIt++;
							}
						}
					} else {
						while ( currentItem.regIt != regExp.getEnd() ) {
							if ( *currentItem.regIt == T( '\\' ) ) {
								currentItem.regIt++;
								if ( currentItem.regIt == regExp.getEnd() )
									return true;
								goto backetNormalChar;
							} else if ( *currentItem.regIt == T( '-' ) && currentItem.regIt + 1 != regExp.getEnd() && ( *( currentItem.regIt - 1 ) < *currentItem.strIt && *( currentItem.regIt + 1 ) > *currentItem.strIt ) ) {
								currentItem.strIt++;
								goto bracketSuccess;
							} else if ( *currentItem.regIt == T( ']' ) ) {
								insideBracket = false;
								goto noMatchBracket;
							} else backetNormalChar: if ( *currentItem.strIt == *currentItem.regIt ) {
								currentItem.strIt++;
								goto bracketSuccess;
							} else {
								currentItem.regIt++;
							}
						}
					}

					return true;

bracketSuccess:
					while ( *currentItem.regIt != T( ']' ) ) {
						if ( *currentItem.regIt == T( '\\' ) ) {
							currentItem.regIt++;
							if ( currentItem.regIt == regExp.getEnd() )
								return true;
						}
						currentItem.regIt++;
						if ( currentItem.regIt == regExp.getEnd() ) return true;
					}
					continue;

				}




			} else {
				if ( *currentItem.regIt == T( '\\' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					goto normalChar;
				} else if ( *currentItem.regIt == T( '[' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					stack.push( { currentItem.strIt, currentItem.regIt, 0 } );
					insideBracket = true;
				} else if ( *currentItem.regIt == T( '$' ) ) {
					if ( currentItem.strIt == str.getEnd() )
						return true;
					else
						return false;
				} else if ( *currentItem.regIt == T( '(' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					stack.push( { currentItem.strIt, currentItem.regIt, 0 } );
				} else if ( *currentItem.regIt == T( ')' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					if ( *currentItem.regIt == T( '+' ) || *currentItem.regIt == T( '*' ) ) {
						currentItem.regIt = stack.getLast().regIt;
						stack.getLast().strIt = currentItem.strIt;
						stack.getLast().actualIteration++;
					} else
						stack.pop();

				} else if ( *currentItem.regIt == T( '+' ) ) {
					currentItem.regIt--;
					currentItem.actualIteration++;
				} else if ( *currentItem.regIt == T( '*' ) ) {
					currentItem.regIt--;
					currentItem.actualIteration++;
				} else if ( *currentItem.regIt == T( '?' ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
				} else if ( *currentItem.regIt == T( '|' ) ) {			//We have reached a pipe but we matched until this
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					for ( int level = 0; true; currentItem.regIt++ ) {
						if ( currentItem.regIt == regExp.getEnd() )
							return true;
						else if ( *currentItem.regIt == T( '\\' ) ) {
							currentItem.regIt++;
							if ( currentItem.regIt == regExp.getEnd() )
								return true;
						} else if ( *currentItem.regIt == T( '(' ) ) {
							level++;
						} else if ( *currentItem.regIt == T( ')' ) ) {
							if ( level == 0 )
								break;
							level--;
						} else if ( *currentItem.regIt == T( '$' ) ) {
							if ( currentItem.strIt == str.getEnd() )
								return true;
							else {

								if ( forceBeginStr ) {
									return false;
								} else {
									StackItem & firstItem = stack.getFirst();
									firstItem.strIt++;
									if ( str.getEnd() == firstItem.strIt )		//If we test the whole string and nothing founded
										return true;
									else {
										currentItem.regIt = firstItem.regIt;	//If not, we have advanced from one char, reset the regex and go.
										currentItem.strIt = firstItem.strIt;
										break;
									}


								}
							}
						}
					}
				} else normalChar:if ( currentItem.strIt != str.getEnd() && ( *currentItem.strIt == *currentItem.regIt || *currentItem.regIt == T( '.' ) ) ) {	//The character is Correct
					currentItem.regIt++;
					currentItem.strIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;

					currentItem.actualIteration = 0;
				} else {
					goto noMatch;
				}
			}

			continue;


noMatch:
			//Check if we have direct +, *, ? after the current char
			if ( currentItem.regIt + 1 != regExp.getEnd() ) {
				currentItem.regIt++;

				if ( *currentItem.regIt == T( '?' ) || *currentItem.regIt == T( '*' ) || ( *currentItem.regIt == T( '+' ) && currentItem.actualIteration ) ) {
					currentItem.regIt++;
					if ( currentItem.regIt == regExp.getEnd() )
						return true;
					continue;
				}
				currentItem.regIt--;
			}
noMatchBracket:
			unsigned int level = 0;

			int usefullLevel = 0;
			bool insideBracket2 = insideBracket;
			for ( auto it = currentItem.regIt; true; it++ ) {
				if ( it == regExp.getEnd() ) {	//If we are at the end of the regex without matching

					if ( forceBeginStr ) {
						return false;
					} else {
						StackItem & firstItem = stack.getFirst();
						firstItem.strIt++;
						if ( str.getEnd() == firstItem.strIt )		//If we test the whole string and nothing founded
							return false;
						else {
							currentItem.regIt = firstItem.regIt;	//If not, we have advanced from one char, reset the regex and go.
							currentItem.strIt = firstItem.strIt;
							break;
						}


					}

				}
				if ( *it == T( '\\' ) ) {		//A backslash is not interpreted, dont care
					it++;
					if ( it == regExp.getEnd() )
						return false;
				} else if ( *it == T( '[' ) ) {
					level++;
					insideBracket2 = true;
				} else if ( *it == T( ']' ) ) {
					if ( level == usefullLevel && level == 0 ) {
						auto itIncr = it + 1;
						if ( itIncr == regExp.getEnd() )
							return false;
						if ( *itIncr == T( '?' ) || *itIncr == T( '*' ) || ( *itIncr == T( '+' ) && stack.getLast().actualIteration ) ) {

							it = itIncr;
							itIncr++;
							if ( itIncr == regExp.getEnd() )
								return true;
							currentItem.strIt = stack.pop().strIt;
							currentItem.regIt = itIncr;
							insideBracket = false;
							break;
						}
						insideBracket = false;
						currentItem.strIt = stack.pop().strIt;

						usefullLevel = level - 1;
					}
					level--;
					insideBracket2 = false;
				} else if ( insideBracket2 ) {
					//If we are inside the current level
					if ( usefullLevel == 0 ) {
						//do some test like a-z....
						//Or not.
					}
				} else if ( *it == T( '(' ) ) {
					level++;
				} else if ( *it == T( '|' ) && level == usefullLevel ) {
					//Houra with a condition branch, test it !
					auto itIncr = it + 1;
					if ( itIncr == regExp.getEnd() )
						return false;
					currentItem.strIt = stack.getLast().strIt;
					currentItem.regIt = itIncr;
					break;
				} else if ( *it == T( ')' ) ) {

					if ( level == usefullLevel ) {
						auto itIncr = it + 1;
						if ( itIncr == regExp.getEnd() )
							return false;
						if ( *itIncr == T( '?' ) || *itIncr == T( '*' ) || ( *itIncr == T( '+' ) && stack.getLast().actualIteration ) ) {

							it = itIncr;
							itIncr++;
							if ( itIncr == regExp.getEnd() )
								return true;
							currentItem.strIt = stack.pop().strIt;
							currentItem.regIt = itIncr;
							insideBracket = false;
							break;
						}
						insideBracket = false;

						currentItem.strIt = stack.pop().strIt;

						usefullLevel = level - 1;
					}
					level--;
				}
			}
		}
		return false;
	}
}
