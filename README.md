
Democracy OOP Project

This is my OOP project where I used the topic of democracy to show polymorphism and object oriented concepts.
I made a class called DemocraticSystem that keeps track of the country name, number of voters, number of political parties and who the leader is.

Then I made actions that can change those values, like changing the number of voters or changing the leader.
Each action is a class that inherits from DemocraticAction which is a base class with an apply() function.

Main OOP concepts I used:
- Polymorphism: I used one base class pointer to apply different actions.
- Inheritance: all actions are subclasses of the same base class.
- Encapsulation: I used private variables with getter/setter.
- Abstraction: only necessary stuff is visible.

I also added some test cases to check that the values change correctly and to test the calculations.

To compile it just use:
g++ Democracy.cpp -o democracy
./democracy

This is just for learning and not real politics lol.
