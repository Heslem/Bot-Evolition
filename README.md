# Bot-Evolition

This is small project for Orange PI, and this not mistake in name. I want to run it on a few days, or weeks. Maybe in future i add neural networks.

My code bad? Yes. I will happy is you try to help me.

# Logic of bot
Any bots have "brain", array of commands (numbers)
Command "1" can mean move left. Command "2" move right.
So, commands can be with arguments. Command "5" have one argument. This argument mean side where the bot spawn a new bot.

List of commands:
1 - move left
2 - move right
3 - move down
4 - move up
5 - spawn(side)
6 - kill(side)
7 - get food from light.
8 - goto(pointer)

9 - if(condition, end pointer)

the end pointer means where the counter is set if the condition is false.

condition list:
1 - left bot
2 - right bot
3 - down bot
4 - up bot
