from player import Player
from room import Room

def load_rooms(filename):
    """
    Load rooms from filename.
    Returns a list of Room objects.
    """
    rooms = []
    with open(filename, "r") as f:

        # read file line by line
        line_content = []
        options = []
        moves_start = False

        # this is a very terrible implementation of parsing the file
        for line in f:

            # check if regular info or movement options
            # if it's an enter, make object and clean data
            if line == "\n":
                rooms.append(Room(line_content[0], line_content[1], line_content[2], options))
                line_content = []
                options = []
                moves_start = False
            # if it's info about the room
            elif line != "-----\n" and not moves_start:
                line_content.append(line)
            # if it's moves info
            elif line != "-----\n" and moves_start:
                options.append(line.strip().split())
            # if it's the ----- line indicating the moves are about to follow
            else:
                moves_start = True

        return rooms

def won():
    """
    Check if the player has won the game.
    Returns the appropriate Boolean.
    """
    return False

def move_print(player):
    """
    Print stuff for every move.
    """
    print("------------------")
    print(player.current_room.name)
    print(player.current_room.description)
    print("Where do you want to go?")
    for option in player.current_room.options:
        print(option[0])

def play(game):
    """
    Play an Adventure game
    """
    rooms = load_rooms(f"data/{game}Rooms.txt")

    # here we create a player object filled with some dummy variables.
    player_1 = Player(42, "Player 1", rooms)
    print(f"Welcome, {player_1.name}, to the Adventure games.\n"
        "May the randomly generated numbers be ever in your favour.\n")

    # a collection of valid commands to be used in the player.move method.
    moves = set(["EAST", "WEST", "SOUTH", "IN", "OUT", "DOWN"])

    # prompt the user for commands until they've won the game.
    while not won():

        # print current location and options
        move_print(player_1)

        # prompt user for input
        command = input("> ")

        # if the move is allowed at all
        if command in moves:
            player_1.move(command)
        else:
            print("\nInvalid command!")



if __name__ == "__main__":
    game = "Tiny"
    play(game)
