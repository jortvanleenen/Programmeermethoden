/**
 * Programming Methods - Assignment 3: Life (16/11/2021)
 *
 * Made with: Code::Blocks, CLion
 * Name: main3.cpp
 * Compiler: GCC 7.2.0 (via MingW-W64-builds 5.0.3)
 *
 * This program is a command-line version of Conway's 'Game of Life'. It makes
 * use of a character representation for alive and dead cells to visualize each
 * generation. It also shows a menu below the game field with various options
 * to manipulate parameters within the game.
 *
 * The Life-class itself contains all required functions for Conway's
 * 'Game of Life', which are being used by the menu-items.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Forward declaration of showInformation()
void showInformation();

// Forward declaration of startLife()
void startLife();

/**
 * The user will be shown information about this program, the game itself and
 * various menu-items. The game will then be started and an empty game world
 * shall be generated. Afterwards a menu shall be shown with various game
 * manipulation options.
 *
 * @return EXIT_SUCCES on success
 */
int main() {

  showInformation();

  // Opens the 'Game of Life' menu, which first shows an empty Life-world once
  startLife();

  return EXIT_SUCCESS;
}

/**
 * Class containing all variables and functions required for the 'Game of Life'.
 */
class Life {
private:
  // These constants can be changed before making use of this class to change
  // the default view and world size
  static const int m_world_row{1001};
  static const int m_world_column{1001};
  const int m_view_height{25};
  const int m_view_width{85};

  bool m_world[m_world_row][m_world_column]{false};
  bool m_temp[m_world_row][m_world_column]{false};

  // Coordinates of the upper left corner
  int m_view_row{static_cast<int>(m_world_row / 2)
                 - static_cast<int>(m_view_height / 2)};
  int m_view_column{static_cast<int>(m_world_column / 2)
                    - static_cast<int>(m_view_width / 2)};

  // Coordinates of the cursor placed in the middle of the view by default
  int m_cursor_row{static_cast<int>(m_world_row / 2)};
  int m_cursor_column{static_cast<int>(m_world_column / 2)};

  int m_percentage{50};
  int m_stepsize{1};
  char m_cell_alive{'#'};
  char m_cell_dead{'-'};

  // Methods for private usage
  static int randomNumber();

  void calculateGeneration();

public:
  // We explicitly indicate a default-constructor should be made to prevent it
  // from being removed when other constructors are added to this class later
  Life() = default;

  void clear(bool only_view);

  void toggle();

  void random();

  void load();

  void print(int generations);

  void moveUp(bool cursor);

  void moveLeft(bool cursor);

  void moveDown(bool cursor);

  void moveRight(bool cursor);

  // We have added various getters and setters yet unused by the program to
  // accommodate the future needs of possible implementors
  int getPercentage() const { return m_percentage; }

  void setPercentage(int percentage) { m_percentage = percentage; }

  int getStepsize() const { return m_stepsize; }

  void setStepsize(int stepsize) { m_stepsize = stepsize; }

  char getCellAlive() const { return m_cell_alive; }

  void setCellAlive(char cell_alive) { m_cell_alive = cell_alive; }

  char getCellDead() const { return m_cell_dead; }

  void setCellDead(char cell_dead) { m_cell_dead = cell_dead; }

  int getViewHeight() const { return m_view_height; }

  int getViewWidth() const { return m_view_width; }

  int getViewRow() const { return m_view_row; }

  void setViewRow(int view_row) { m_view_row = view_row; }

  int getViewColumn() const { return m_view_column; }

  void setViewColumn(int view_column) { m_view_column = view_column; }

  int getCursorRow() const { return m_cursor_row; }

  void setCursorRow(int cursor_row) { m_cursor_row = cursor_row; }

  int getCursorColumn() const { return m_cursor_column; }

  void setCursorColumn(int cursor_column) { m_cursor_column = cursor_column; }

  int getWorldRow() const { return m_cursor_column; }

  int getWorldColumn() const { return m_cursor_column; }
};

/**
 * Kills all cells within the world or view, depending on the parameter.
 *
 * @param only_view 'true' if only cells within the view should get killed
 */
void Life::clear(bool only_view) {

  int begin_row{only_view ? m_view_row : 0};
  int begin_column{only_view ? m_view_column : 0};

  int stop_row{only_view ? (m_view_row + m_view_height) : m_world_row};
  int stop_column{only_view ? (m_view_column + m_view_width)
                            : m_world_column};

  for (int i = begin_row; i < stop_row; i++) {
    for (int j = begin_column; j < stop_column; j++) {
      m_world[i][j] = false;
    }
  }
}

/**
 * Asks the user for a character. Preceding non-alphabetical characters get
 * ignored/removed. When multiple characters are entered these are ignored for
 * this request.
 *
 * @return the first alphabetical character entered by the user
 */
char askInput() {

  char input{};

  // Keeps reading the stream until we read an alphabetical character
  do {
    input = static_cast<char>(std::cin.get());
  } while (input < ' ');

  return input;
}

/**
 * Moves the cursor or view 'stepsize'-amount up.
 *
 * @param cursor 'true' when the cursor needs to be moved
 */
void Life::moveUp(bool cursor) {
  if (cursor) {
    if ((m_cursor_row - m_stepsize) >= m_view_row) {
      m_cursor_row -= m_stepsize;
    } else {
      m_cursor_row = m_view_row;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  } else {
    if (m_view_row - m_stepsize >= 0) {
      m_view_row -= m_stepsize;
    } else {
      m_view_row = 0;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  }
}

/**
 * Moves the cursor or view 'stepsize'-amount to the left.
 *
 * @param cursor 'true' when the cursor needs to be moved
 */
void Life::moveLeft(bool cursor) {
  if (cursor) {
    if ((m_cursor_column - m_stepsize) >= m_view_column) {
      m_cursor_column -= m_stepsize;
    } else {
      m_cursor_column = m_view_column;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  } else {
    if (m_view_column - m_stepsize >= 0) {
      m_view_column -= m_stepsize;
    } else {
      m_view_column = 0;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  }
}

/**
 * Moves the cursor or view 'stepsize'-amount down.
 *
 * @param cursor 'true' when the cursor needs to be moved
 */
void Life::moveDown(bool cursor) {
  if (cursor) {
    if ((m_cursor_row + m_stepsize) <= (m_view_row + m_view_height)) {
      m_cursor_row += m_stepsize;
    } else {
      m_cursor_row = (m_view_row + m_view_column);
      std::cout << "The edge of the world was reached during the move.\n";
    }
  } else {
    if ((m_view_row + m_stepsize) < m_world_row) {
      m_view_row += m_stepsize;
    } else {
      m_view_row = m_world_row - 1;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  }
}

/**
 * Moves the cursor or view 'stepsize'-amount to the right.
 *
 * @param cursor 'true' when the cursor needs to be moved
 */
void Life::moveRight(bool cursor) {
  if (cursor) {
    if ((m_cursor_column + m_stepsize)
        <= (m_view_column + m_view_width)) {
      m_cursor_column += m_stepsize;
    } else {
      m_cursor_column = (m_view_column + m_view_width);
      std::cout << "The edge of the world was reached during the move.\n";
    }
  } else {
    if ((m_view_column + m_stepsize) < m_world_column) {
      m_view_column += m_stepsize;
    } else {
      m_view_row = m_world_column - 1;
      std::cout << "The edge of the world was reached during the move.\n";
    }
  }
}

/**
 * Shows a menu through which move operations can be performed.
 *
 * @param life life-object in which the move operation takes place
 * @param cursor 'true' when the cursor needs to get moved
 * @param direction 'W' - up, 'A' - left, 'S' - right, 'D' - down
 */
void moveMenu(Life &life, bool cursor, char direction) {

  char input{static_cast<char>(toupper(direction))};

  if (input != 'W' && input != 'A' && input != 'S' && input != 'D') {
    std::cout << "Move: [B]ack, [W]Up, [A]Left, [S]Down, [D]Right\n";
    input = static_cast<char>(toupper(askInput()));
  }

  do {
    switch (input) {
      case 'B':
        // Exit menu because of while-condition
        break;
      case 'W':
        life.moveUp(cursor);
        break;
      case 'A':
        life.moveLeft(cursor);
        break;
      case 'S':
        life.moveDown(cursor);
        break;
      case 'D':
        life.moveRight(cursor);
        break;
      default:
        std::cout << "Unknown action, please try again!\n";
        break;
    }

    if (input == 'W' || input == 'A' || input == 'S' || input == 'D') {
      life.print(0);
    }

    if (cursor) {
      // We leave the do-while loop by forcing back as input
      input = 'B';
    } else if (input != 'B') {
      std::cout << "Move: [B]ack, [W]Up, [A]Left, [S]Down, [D]Right\n";
      input = static_cast<char>(toupper(askInput()));
    }

  } while (input != 'B');
}

/**
 * Changes the state of the cell below the cursor/on the cursor position.
 * (alive -> dead and dead -> alive)
 *
 * Forcing alive cells on the edge of the world is possible, but they get
 * automatically removed after one iteration/generation takes place.
 */
void Life::toggle() {
  m_world[m_cursor_row][m_cursor_column] =
      !m_world[m_cursor_row][m_cursor_column];
}

/**
 * Generates a random number between 0-999 based on a seed.
 *
 * @return a random integer between 0-999
 */
int Life::randomNumber() {
  // We had to make use of this exact function body
  static int number = static_cast<int>(time(nullptr));
  number = (221 * number + 1) % 1000;
  return number;
}

/**
 * Fills the view with 'm_percentage'% of alive cells by making use of the
 * randomNumber-generator built into the Life-class.
 */
void Life::random() {

  for (int i = 0; i < m_view_height; i++) {

    for (int j = 0; j < m_view_width; j++) {

      if (randomNumber() < (m_percentage * 10)) {
        m_world[m_view_row + i][m_view_column + j] = true;
      } else {
        m_world[m_view_row + i][m_view_column + j] = false;
      }
    }
  }
}

/**
 * Loads an external, text-based configuration into the world. When an error
 * occurs during import, the import gets aborted. Previously imported data
 * shall not be made undone.
 *
 * An external configuration file may only consist of newline-characters, ones
 * for alive cells and zeros for dead cells.
 *
 * When a to-be imported row or column is bigger than the allowed size by the
 * world dimensions, all 'too big' elements get ignored silently.
 */
void Life::load() {

  std::ifstream input{};
  std::string input_path{};

  // Keep trying to create an import stream until successful
  do {
    std::cout << "Give the location to the configuration and press ENTER:\n";
    std::cin >> input_path;

    input.open(input_path);

    if (!input) {
      std::cout << "Could not find the configuration, please try again!\n";
    }

  } while (!input);

  char kar = static_cast<char>(input.get());

  int row_number{0};
  int column_number{0};

  // Keep going through the file until an error occurs or the end has been
  // reached
  while (input) {

    switch (kar) {
      case '0':
        if (m_view_column + column_number + 1 < m_world_column) {
          m_world[m_view_row + row_number][m_view_column + column_number]
              = false;
          column_number++;
        }
        break;
      case '1':
        if (m_view_column + column_number + 1 < m_world_column) {
          m_world[m_view_row + row_number][m_view_column + column_number] = true;
          column_number++;
        }
        break;
      case '\n':
        column_number = 0;
        if (m_view_row + row_number + 1 < m_world_row) {
          row_number++;
        }
        break;
      default:
        std::cout << "Import aborted: invalid character in configuration"
                     " file!\n";
        return;
    }

    kar = static_cast<char>(input.get());
  }

  // When we do not exit the while-loop because the end of the configuration has
  // been reached, an error has occurred
  if (!input.eof()) {
    std::cout << "Import has been aborted prematurely because of an error!\n";
  }
}

/**
 * Calculates the next generation of cells within the world.
 * Rule 1: Alive cells stay alive with two or three alive neighbours, otherwise
 * they die.
 * Rule 2: Dead cells become alive when having exactly three alive neighbours,
 * otherwise they stay dead.
 */
void Life::calculateGeneration() {

  int alive_neighbours{};

  for (int i = 0; i < m_world_row; i++) {
    for (int j = 0; j < m_world_column; j++) {

      if ((i - 1 >= 0) && m_world[i - 1][j]) {
        alive_neighbours++;
      }
      if ((j - 1 >= 0) && m_world[i][j - 1]) {
        alive_neighbours++;
      }
      if ((i - 1 >= 0) && (j - 1 >= 0) && m_world[i - 1][j - 1]) {
        alive_neighbours++;
      }
      if ((i + 1 < m_world_row) && m_world[i + 1][j]) {
        alive_neighbours++;
      }
      if ((j + 1 < m_world_column) && m_world[i][j + 1]) {
        alive_neighbours++;
      }
      if ((i + 1 < m_world_row) && (j + 1 < m_world_column)
          && m_world[i + 1][j + 1]) {
        alive_neighbours++;
      }
      if ((i - 1 >= 0) && (j + 1 < m_world_column) && m_world[i - 1][j + 1]) {
        alive_neighbours++;
      }
      if ((i + 1 < m_world_row) && (j - 1 >= 0) && m_world[i + 1][j - 1]) {
        alive_neighbours++;
      }

      if (m_world[i][j]) {
        // The cell is alive
        if (alive_neighbours == 2 || alive_neighbours == 3) {
          // with two or three neighbours it stays alive
          m_temp[i][j] = true;
        }
      } else {
        if (alive_neighbours == 3) {
          // The cell is dead, with exactly three neighbours it becomes alive
          m_temp[i][j] = true;
        }
      }

      alive_neighbours = 0;
    }
  }

  // Place the just calculated generation into the world
  for (int i = 0; i < m_world_row; i++) {
    for (int j = 0; j < m_world_column; j++) {
      // Kills all cells at the borders of the world
      if (i == 0 || j == 0 || i == (m_world_row - 1)
          || j == (m_world_column - 1)) {
        m_world[i][j] = false;
      } else {
        m_world[i][j] = m_temp[i][j];
      }
      // Reset the temporary world for next calculations
      m_temp[i][j] = false;
    }
  }
}

/**
 * Prints a certain amount of generations, depending on the input parameter.
 * Negative input is allowed, but is corrected to zero generations.
 *
 * An input of zero generations shall display the field once, but without the
 * cells advancing a single generation. Useful for showing the field in a static
 * state.
 *
 * @param generations amount of generations that the world needs to advance
 */
void Life::print(int generations) {

  int row_in_world{};
  int column_in_world{};

  if (generations < 0) {
    generations = 0;
  }

  // The amount of to-be printed generations
  for (int i = (generations == 0 ? -1 : 0); i < generations; i++) {

    // The amount of to-be printed rows
    for (int j = 0; j < m_view_height; j++) {

      row_in_world = m_view_row + j;

      // The amount of to-be printed columns
      for (int k = 0; k < m_view_width; k++) {

        column_in_world = m_view_column + k;

        if (((row_in_world) == m_cursor_row) &&
            ((column_in_world) == m_cursor_column)) {
          // Places an '*' as cursor on an alive cell and a 'X' as cursor on
          // a dead cell
          std::cout << (m_world[row_in_world][column_in_world] ? '*' : 'X');
        } else {
          std::cout << (m_world[row_in_world][column_in_world] ?
                        m_cell_alive : m_cell_dead);
        }
      }
      std::cout << "\n";
    }

    // Coordinates of the upper left corner of the view
    std::cout << "View: (" << m_view_row << ", " << m_view_column << ") ";

    // Calculates the amount of delimiters to be placed based on the size
    // of the view and printed coordinates
    int delimiter_count =
        static_cast<int>(m_view_width - std::to_string(m_view_row).length()
                         - std::to_string(m_view_column).length() - 11
                         - std::to_string(m_cursor_row).length()
                         - std::to_string(m_cursor_column).length() - 13);

    // Places a row with '=' to act as delimiters
    for (int k = 0; k < delimiter_count; k++) {
      std::cout << "=";
    }

    // Coordinates of the cursor
    std::cout << " Cursor: (" << m_cursor_row << ", " << m_cursor_column
              << ")\n";

    // Calculate the next generation of cells, except for when the amount of to-
    // be shown generations is equal to 0
    if (generations != 0) {
      calculateGeneration();
    }
  }
}

/**
 * Asks the user for a number. Preceding non-alphabetical characters get
 * removed.
 *
 * Example: [enter]34hshf4hh3 -> 3443; With a max of 500: 3443 -> 344.
 *
 * @param max the maximal size of the number to get returned
 * @return the number extracted from the user input between 0-max
 */
int askNumber(int max) {

  int number{};
  char input{askInput()};

  do {
    if ((input >= '0' && input <= '9') &&
        (10 * number + (input - '0') <= max)) {
      number = 10 * number + (input - '0');
    }

    input = static_cast<char>(std::cin.get());

  } while (input != '\n' && input);

  return number;
}

/**
 * Asks for a number between 0-100, which shall be used as new value for the
 * member-variable 'percentage' of the Life-object.
 *
 * @param life Life-object to get manipulated
 */
void givePercentage(Life &life) {
  std::cout << "Current percentage: " << life.getPercentage()
            << "%\nGive a percentage between 0-100% and press ENTER:\n";

  life.setPercentage(askNumber(100));
}

/**
 * Asks for a character, which shall be used as new value for the
 * member-variable representation of an alive or dead cell depending on the
 * parameter.
 *
 * @param life Life-object to get manipulated
 * @param alive 'true' when changing the alive cell, 'false' for the dead cell
 */
void giveRepresentation(Life &life, bool alive) {
  std::cout << "Current representation: '"
            << (alive ? life.getCellAlive() : life.getCellDead())
            << "'\nEnter a character for the "
            << (alive ? "alive " : "dead ")
            << "cell and press ENTER:\n";

  char new_representation{askInput()};

  // if-conditions ensure that both representations can never become equal
  if (alive && (life.getCellDead() != new_representation)) {
    life.setCellAlive(new_representation);
  } else if (!alive && (life.getCellAlive() != new_representation)) {
    life.setCellDead(new_representation);
  } else {
    std::cout << "Change denied: the two cell representations may not be equal "
                 "to each other!\n";
  }
}

/**
 * Asks for a number between 0-500, which shall be used as new value for the
 * member-variable 'stepsize' of the Life-object.
 *
 * @param life Life-object to get manipulated
 */
void giveStepsize(Life &life) {
  std::cout << "Current stepsize: " << life.getStepsize()
            << "\nEnter a number between 0-500 and press ENTER:\n";

  life.setStepsize(askNumber(500));
}

/**
 * Opens a menu with options to change the stepsize used with the move command,
 * the percentage of alive cells when using the random command and the visual
 * representation of alive and dead cells when using the print-operation.
 *
 * @param life Life-object to get manipulated
 */
void paramSubmenu(Life &life) {

  char input{};

  do {
    std::cout << "Params: [B]ack, [P]ercentage(" << life.getPercentage()
              << "%), [A]live('" << life.getCellAlive() << "'), [D]ead('"
              << life.getCellDead() << "'), [S]tepsize(" << life.getStepsize()
              << ")\n";
    input = static_cast<char>(toupper(askInput()));

    switch (input) {
      case 'B':
        // Exit submenu because of while-condition
        break;
      case 'P':
        givePercentage(life);
        break;
      case 'A':
        giveRepresentation(life, true);
        break;
      case 'D':
        giveRepresentation(life, false);
        break;
      case 'S':
        giveStepsize(life);
        break;
      default:
        std::cout << "Unknown action, please try again!\n";
        break;
    }
  } while (input != 'B');
}

/**
 * Creates a new Life-object which it prints to the command-line. Afterwards
 * it shows a menu with various manipulation options regarding the object.
 */
void startLife() {

  Life life{};
  int generations{0};

  life.print(generations);

  char input{};

  do {

    std::cout << "[E]xit, [K]ill, [C]lear, [M]ove, [P]arams, [R]andom, "
                 "[T]oggle, [L]oad, [O]ne, [G]o\n";
    input = static_cast<char>(toupper(askInput()));

    switch (input) {
      case 'E':
        // Exit menu because of while-condition
        generations = -1;
        break;
      case 'K':
        life.clear(false);
        break;
      case 'C':
        life.clear(true);
        break;
      case 'M':
        moveMenu(life, false, ' ');
        generations = -1;
        break;
      case 'P':
        paramSubmenu(life);
        break;
      case 'T':
        life.toggle();
        break;
      case 'R':
        life.random();
        break;
      case 'L':
        life.load();
        break;
      case 'O':
        generations = 1;
        break;
      case 'G':
        generations = 30;
        break;
      case 'W':
        moveMenu(life, true, 'w');
        generations = -1;
        break;
      case 'A':
        moveMenu(life, true, 'a');
        generations = -1;
        break;
      case 'S':
        moveMenu(life, true, 's');
        generations = -1;
        break;
      case 'D':
        moveMenu(life, true, 'd');
        generations = -1;
        break;
      default:
        std::cout << "Unknown action, please try again!\n";
        generations = -1;
        break;
    }

    if (generations != -1) {
      life.print(generations);
    }

    generations = 0;

  } while (input != 'E');
}

/**
 * Shows useful program-related information to the user.
 */
void showInformation() {
  std::cout << "Programming Methods - Assignment 3: Life (16/11/2021)\n"
               "This program is a command-line based version of Conway's Game"
               "of Life.\nIt works by providing character-representations for"
               "dead and alive cells.\nIt also shows a menu with various "
               "options to manipulate the game with.\n"
               "\tExit (E/e) - exit program\n"
               "\tKill (K/k) - kill all living cells within the world\n"
               "\tClear (C/c) - kill all living cells within the view\n"
               "\tMove (M/m) - shift the view within the world\n"
               "\tParams (P/p) - contain options to change parameters\n"
               "\tToggle  (T/t) - switch cell state of the cell at cursor\n"
               "\tCursor (Ww/Aa/Ss/Dd) - move cursor through the world\n"
               "\tRandom (R/r) - fill the view with random alive cells\n"
               "\tLoad (L/l) - load an external file into the world\n"
               "\tOne (O/o) - make the cells 1 generation older\n"
               "\tGo (G/g) - make the cells 30 generations older\n\n"
               "\tCommandos can be chained, e.g.:\n"
               "\tpp40: params -> percentage -> 40%\n";
}
