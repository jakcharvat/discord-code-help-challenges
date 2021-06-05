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

type TicTacToeState = { 
    currentPlayer: Player, 
    board: Board
}

const initialState: TicTacToeState = {
    currentPlayer: Player.Cross,
    board: [
        [ 0, 0, 0 ],
        [ 0, 0, 0 ],
        [ 0, 0, 0 ]
    ]
}
const ticTacToeStore = writable(deepcopy(initialState))
const gameState = derived(ticTacToeStore, state => state)

function deepcopy(state: TicTacToeState): TicTacToeState {
    return {
        currentPlayer: state.currentPlayer,
        board: state.board.map(row => Object.assign([], row))
    }
}

function encode(state: TicTacToeState): string {
    return `${state.currentPlayer}${state.board.map(row => row.map((p) => +p).join('')).join('')}`
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

    return {
        currentPlayer: +str[0],
        board: board
    }
}


/* ------------------------------------------------- PLAY ------------------------------------------------- */
function play(row: number, col: number) {
    ticTacToeStore.update(curr => {
        if (curr.board[row][col]) { return curr }
        if (row < 0 || row >= curr.board.length) { return curr }
        if (col < 0 || col >= curr.board[0].length) { return curr }

        if (checkWin(curr.board, curr.currentPlayer, row, col)) {
            console.log('win')
        }

        let newState = deepcopy(curr)
        newState.board[row][col] = curr.currentPlayer
        newState.currentPlayer = otherPlayer(curr.currentPlayer)

        console.log(newState)
        console.log(decode(encode(newState)))
        console.log(encode(newState))

        return newState
    })
}


/* ----------------------------------------------- CHECK WIN ---------------------------------------------- */
function checkWin(board: Board, player: Player, row: number, col: number): boolean {
    // either one on each side, or two to one side
    const neighbours = [[1, -1], [1, 0], [1, 1], [0, 1]] // plus their reverse

    const blockAt = (row: number, col: number) => {
        if (board[row]) {
            return board[row][col]
        }
        return null
    }
    
    for (const [addY, addX] of neighbours) {
        if (blockAt(row + addY, col + addX) === player) {
            // two in the original direction
            if (blockAt(row + 2*addY, col + 2*addX) === player) { return true }
            // one on either side of the newest block
            if (blockAt(row - addY, col - addX) === player) { return true }
        } else if (blockAt(row - addY, col - addX) === player) {
            // two in the opposite direction
            if (blockAt(row - 2*addY, col - 2*addX) === player) { return true }
        }
    }

    return false
}



export type { TicTacToeState }
export { gameState, play, Player }
