import { derived, writable } from 'svelte/store'


/* ------------------------------------------------ PLAYER ------------------------------------------------ */
enum Player {
    Cross = 1,
    Naught,
}

function otherPlayer(player: Player): Player {
    switch (player) {
        case Player.Cross: return Player.Naught
        case Player.Naught: return Player.Cross
    }
}


/* ------------------------------------------------- STATE ------------------------------------------------ */
type Board = (Player)[][]

type WinInfo = {
    direction: WinDirection,
    winningX: number,
    winningY: number
}

type TicTacToeState = { 
    currentPlayer: Player, 
    board: Board,
    win: (WinInfo | null)
}

const initialState: TicTacToeState = {
    currentPlayer: Player.Cross,
    board: [
        [ 0, 0, 0 ],
        [ 0, 0, 0 ],
        [ 0, 0, 0 ]
    ],
    win: null
}
const ticTacToeStore = writable(deepcopy(initialState))
const gameState = derived(ticTacToeStore, state => state)

function deepcopy(state: TicTacToeState): TicTacToeState {
    return {
        currentPlayer: state.currentPlayer,
        board: state.board.map(row => Object.assign([], row)),
        win: state.win ? Object.assign({}, state.win) : null
    }
}

function encode(state: TicTacToeState): string {
    const currPlayer = `${state.currentPlayer}`
    const board = `${state.board.map(row => row.map(p => +p).join('')).join('')}`
    const win = () => {
        if (!state.win) { return '' }
        const dir = `${state.win.direction}`
        const x = `${state.win.winningX}`
        const y = `${state.win.winningY}`
        return dir + x + y
    }
    return currPlayer + board + win()
}

function decode(str: string): TicTacToeState {
    const board: Board = []
    for (let i = 0; i < 3; i++) {
        const row: number[] = []
        for (let j = 0; j < 3; j++) {
            row.push(+str[i*3 + j + 1])
        }
        board.push(row)
    }

    function getWinInfo(): (WinInfo | null) {
        if (str.length <= 10) { return null }
        
        return {
            direction: +str[10],
            winningX: +str[11],
            winningY: +str[12]
        }
    }

    return {
        currentPlayer: +str[0],
        board: board,
        win: getWinInfo()
    }
}


/* ------------------------------------------------- PLAY ------------------------------------------------- */
function play(row: number, col: number) {
    ticTacToeStore.update(curr => {
        if (curr.win) { return curr }
        if (curr.board[row][col]) { return curr }
        if (row < 0 || row >= curr.board.length) { return curr }
        if (col < 0 || col >= curr.board[0].length) { return curr }

        let newState = deepcopy(curr)
        newState.board[row][col] = curr.currentPlayer
        newState.currentPlayer = otherPlayer(curr.currentPlayer)

        const winDirection = checkWin(curr.board, curr.currentPlayer, row, col)
        if (winDirection) {
            newState.win = {
                direction: winDirection,
                winningX: col,
                winningY: row
            }
        }

        console.log(newState)
        console.log(decode(encode(newState)))
        console.log(encode(newState))

        return newState
    })
}


/* ----------------------------------------------- CHECK WIN ---------------------------------------------- */
enum WinDirection {
    horizontal = 1,
    vertical,
    diagonalForward,
    diagonalBack
}

function checkWin(board: Board, player: Player, row: number, col: number): WinDirection | null {
    // either one on each side, or two to one side
    const neighbours = [[0, 1], [1, 0], [1, 1], [1, -1]] // plus their reverse

    const blockAt = (row: number, col: number) => {
        if (board[row]) {
            return board[row][col]
        }
        return null
    }
    
    for (const [idx, [addY, addX]] of neighbours.entries()) {
        const direction: WinDirection = idx+1

        if (blockAt(row + addY, col + addX) === player) {
            // two in the original direction
            if (blockAt(row + 2*addY, col + 2*addX) === player) { return direction }
            // one on either side of the newest block
            if (blockAt(row - addY, col - addX) === player) { return direction }
        } else if (blockAt(row - addY, col - addX) === player) {
            // two in the opposite direction
            if (blockAt(row - 2*addY, col - 2*addX) === player) { return direction }
        }
    }

    return null
}



export type { TicTacToeState }
export { gameState, play, Player }
