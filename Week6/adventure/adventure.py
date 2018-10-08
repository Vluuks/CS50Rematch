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
        # Room(3, 'Inside building', 'You are inside a building, a well house for a large spring.')
        line_content = []
        options = []
        moves_start = False
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

def play(game):
    """
    Play an Adventure game
    """
    rooms = load_rooms(f"data/{game}Rooms.txt")

    # Here we create a player object filled with some dummy variables.
    player_1 = Player(42, "Player 1", rooms[0])
    print(f"Welcome, {player_1.name}, to the Adventure games.\n"
        "May the randomly generated numbers be ever in your favour.\n")

    # A collection of valid commands to be used in the player.move method.
    moves = set(["EAST", "WEST", "SOUTH", "IN", "OUT", "DOWN"])


    # Prompt the user for commands until they've won the game.
    while not won():

        print("------------------")
        print(player_1.current_room.name)
        print(player_1.current_room.description)
        print("Where do you want to go?")
        for option in player_1.current_room.options:
            print(option[0])

        command = input("> ")

        # if the move is allowed at all
        if command in moves:
            # check with options in room
            for option in player_1.current_room.options:

                # if the option is present for that room as  well
                if command == option[0]:
                    print("\nMoving...")
                    print(option[1])
                    player_1.current_room = rooms[int(option[1]) - 1]
        else:
            print("\nInvalid command!")



if __name__ == "__main__":
    game = "Tiny"
    play(game)
