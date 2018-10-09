"""
    cardgame.py
    CS50x "Rematch" 2018
    Implements (unsurprisingly) a game of cards
    Exercise made by Quinten

"""
import random

class Card(object):
    """
        Class that represents a card from a regular
        card game. It has a suit and a value.
    """
    def __init__(self, suit, value):
        self.suit = suit
        self.value = value

    def __str__(self):
        return f"{self.value} of {self.suit}"
    
class Deck(object):
    """
        Deck of aforementioned card objects, which have very
        badly translated names just for the sake of it.
        Initializes an ordered set of cards but also allows
        for shuffling and drawing one from the top.
    """
    def __init__(self):
        self.suits = ["Hearts", "Windows", "Clovers", "Kicks"]
        self.values = ['A','2','3','4','5','6','7','8','9','10','J','Q','K']
        
        self.cards = []
        for suit in self.suits:
            for value in self.values:
                self.cards.append(Card(suit, value))
         
    def __str__(self):
        return f"{len(self.cards)} cards in the deck"
    
    # guess what this does
    def shuffle(self):
        random.shuffle(self.cards)

    # deals card from top of the stack    
    def deal(self):
        if self.cards:
            return self.cards.pop()
        else:
            return "You've dealt all the cards!"
        
# i still can't get over this syntax
if __name__ == "__main__":

    # the best card in the game <3
    c1 = Card("Hearts", "Ace")
    print(c1)
    
    # deck
    d = Deck()
    print(d)
    print(d.cards[0])
    
    # shuffle things up!
    d.shuffle()
    print(d.cards[0])
    print(d)
    
    # deal cards
    c2 = d.deal()
    print(c2)
    print(d)
