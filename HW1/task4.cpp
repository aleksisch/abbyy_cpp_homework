
#include <optional>
#include <bitset>
#include <vector>
#include <array>
#include <functional>

class Solution {
  static constexpr size_t BoardSize = 9;
  using Board = std::vector<std::vector<char>>;
  using BitField = std::bitset<BoardSize>;

  enum class State {
    FAILED,
    MULT_CHOICE,
    UPDATED,
    FILLED,
  };

  class Restrict {
  public:
    static constexpr char empty = '.';

    Restrict(const Board& board) : board(board) {
      for (size_t i = 0; i < board.size(); i++) {
        hor[i] = horRestriction(i);
      }
      for (size_t i = 0; i < board[0].size(); i++) {
        vert[i] = vertRestriction(i);
      }
      for (size_t i = 0; i < 3; i++) {
        for (size_t l = 0; l < 3; l++) {
          squared[i][l] = squareRestriction(3 * i, 3 * l);
        }
      }
    }

    BitField allowed(size_t x, size_t y) const {
      if (board.get().at(x).at(y) != empty) {
        return {};
      } else {
        return (hor[x] | vert[y] | squared[x / 3][y / 3]).flip();
      }
    }

    size_t getNumber(size_t x, size_t y) const {
      auto all_num = allowed(x, y);
      for (size_t num = 0; num < BoardSize; num++) {
        if (all_num.test(num)) {
          return num;
        }
      }
      std::abort();
    }

  private:

    BitField horRestriction(size_t x) {
      BitField result;
      for (const auto &c: board.get()[x]) {
        if (getValue(c)) {
          result.set(*getValue(c));
        }
      }
      return result;
    }

    BitField vertRestriction(size_t x) {
      BitField result;
      for (auto & i : board.get()) {
        const auto c = getValue(i[x]);
        if (c) {
          result.set(c.value());
        }
      }
      return result;
    }

    BitField squareRestriction(size_t x, size_t y) {
      BitField result;
      auto x_start = 3 * (x / 3);
      auto y_start = 3 * (y / 3);
      for (size_t i = x_start; i < x_start + 3; i++) {
        for (size_t j = y_start; j < y_start + 3; j++) {
          const auto val = getValue(board.get()[i][j]);
          if (val) {
            result.set(*val);
          }
        }
      }
      return result;
    }

    std::optional<int> getValue(char c) const {
      if (c != empty) {
        return c - '1';
      } else {
        return std::nullopt;
      }
    }

  private:
    std::array<BitField, BoardSize> hor;
    std::array<BitField, BoardSize> vert;
    std::array<std::array<BitField, 3>, 3> squared;
    std::reference_wrapper<const Board> board;
  };
public:
  void solveSudoku(Board& board) {
    auto x = solver(board);
  }

private:

  bool solver(Board &board) {
    State state1 = fill(board);
    while (true) {
      switch (state1) {
        case State::FILLED:
          return true;
        case State::UPDATED:
          state1 = fill(board);
          break;
        case State::FAILED:
          return false;
        case State::MULT_CHOICE: {
          std::pair<size_t, size_t> res = {-1, -1};
          size_t mi = 9;
          const auto constraint = Restrict(board);
          for (int i = 0; i < BoardSize; i++) {
            for (int l = 0; l < BoardSize; l++) {
              if (board[i][l] == Restrict::empty) {
                auto maybe_res = constraint.allowed(i, l);
                if (maybe_res.count() == 0) {
                  return false;
                }
                if (maybe_res.count() < mi) {
                  res = std::make_pair(i, l);
                  mi = maybe_res.count();
                }
              }
            }
          }
          const auto allowed = constraint.allowed(res.first, res.second);
          for (int l = 0; l < BoardSize; l++) {
            if (allowed.test(l)) {
              auto prev = board;
              board[res.first][res.second] = l + '1';
              if (solver(board)) {
                return true;
              } else {
                board = prev;
              }
            }
          }
          return false;
        }
      }
    }
  }

  State fill(Board &board) {
    State changed = State::FAILED;
    auto restr = Restrict(board);
    for (size_t i = 0; i < BoardSize; i++) {
      for (size_t l = 0; l < BoardSize; l++) {
        const auto bitField = restr.allowed(i, l);
        if (bitField.count() == 0) {
          continue;
        }
        if (bitField.count() == 1) {
          board[i][l] = restr.getNumber(i, l) + '1';
          restr = Restrict(board);
          changed = State::UPDATED;
        } else if (changed != State::UPDATED) {
          changed = State::MULT_CHOICE;
        }
      }
    }
    auto full = !std::any_of(
      std::begin(board), std::end(board),
      [letterToFind = Restrict::empty](auto inner) {
        return std::find(std::begin(inner), std::end(inner), letterToFind) != end(inner);
      }
    );
    if (full) {
      return State::FILLED;
    }
    return changed;
  }
};

int main() {
  std::vector<std::vector<char>> x = {{'.','.','.','2','.','.','.','6','3'},
                                      {'3','.','.','.','.','5','4','.','1'},
                                      {'.','.','1','.','.','3','9','8','.'},
                                      {'.','.','.','.','.','.','.','9','.'},
                                      {'.','.','.','5','3','8','.','.','.'},
                                      {'.','3','.','.','.','.','.','.','.'},
                                      {'.','2','6','3','.','.','5','.','.'},
                                      {'5','.','3','7','.','.','.','.','8'},
                                      {'4','7','.','.','.','1','.','.','.'}};
  Solution().solveSudoku(x);
  [[maybe_unusedg]] int xx = 0;
}