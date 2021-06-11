import { derived, writable } from 'svelte/store'
import Module from '$lib/WASM/WASM/gameManager'


/* ------------------------------------------------ PLAYER ------------------------------------------------ */
enum Player {
    Cross = 1,
    Naught,
}


/* ------------------------------------------------- STATE ------------------------------------------------ */
enum WinDirection {
    horizontal = 1,
    vertical,
    diagonalForward,
    diagonalBack
}

function winDirectionClass(winDirection: WinDirection) {
    return {
        1: `win-horizontal`,
        2: `win-vertical`,
        3: `win-diagonal win-diagonal-forward`,
        4: `win-diagonal win-diagonal-back`
    }[winDirection]
}

type Board = (Player)[][]

type WinInfo = {
    direction: WinDirection,
    winningRow: number,
    winningCol: number
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

function deepcopy(state: TicTacToeState): TicTacToeState {
    return {
        currentPlayer: state.currentPlayer,
        board: state.board.map(row => Object.assign([], row)),
        win: state.win ? Object.assign({}, state.win) : null
    }
}


/* --------------------------------------------- GAME MANAGER --------------------------------------------- */
class GameManager {
    private managerInstance: any 
    private ticTacToeStore = writable(deepcopy(initialState))
    gameState = derived(this.ticTacToeStore, state => state)

    private constructor(module: any) {
        this.managerInstance = module
    }

    private static async loadWasm() {
        return await Module()
    }

    private getWinDirection(): WinDirection {
        return this.managerInstance._getWinDirection()
    }

    private getCurrentPlayer(): Player {
        return this.managerInstance._getCurrentPlayer()
    }

    play(row: number, col: number) {
        this.ticTacToeStore.update(currState => {
            const copy = deepcopy(currState)
            const player = this.managerInstance._play(row, col)
            copy.board[row][col] = player

            const direction: WinDirection = this.getWinDirection()
            if (direction && !copy.win) {
                copy.win = {
                    direction: direction,
                    winningRow: row,
                    winningCol: col
                }
            }

            copy.currentPlayer = this.getCurrentPlayer()

            return copy
        })
    }

    static async create(): Promise<GameManager> {
        try {
            const wasm = await GameManager.loadWasm()
            return new GameManager(wasm)
        } catch(e) {
            console.error('Could not instantiate GameManager WASM Module:')
            console.error(e)
        }
    }
}


export default GameManager
export type { WinInfo, TicTacToeState }
export { WinDirection, winDirectionClass, Player }










// // function encode(state: TicTacToeState): string {
// //     const currPlayer = `${state.currentPlayer}`
// //     const board = `${state.board.map(row => row.map(p => +p).join('')).join('')}`
// //     const win = () => {
// //         if (!state.win) { return '' }
// //         const dir = `${state.win.direction}`
// //         const row = `${state.win.winningRow}`
// //         const col = `${state.win.winningCol}`
// //         return dir + row + col
// //     }
// //     return currPlayer + board + win()
// // }

// // function decode(str: string): TicTacToeState {
// //     const board: Board = []
// //     for (let i = 0; i < 3; i++) {
// //         const row: number[] = []
// //         for (let j = 0; j < 3; j++) {
// //             row.push(+str[i*3 + j + 1])
// //         }
// //         board.push(row)
// //     }

// //     function getWinInfo(): (WinInfo | null) {
// //         if (str.length <= 10) { return null }
        
// //         return {
// //             direction: +str[10],
// //             winningRow: +str[11],
// //             winningCol: +str[12]
// //         }
// //     }

// //     return {
// //         currentPlayer: +str[0],
// //         board: board,
// //         win: getWinInfo()
// //     }
// // }


// // /* ------------------------------------------------- PLAY ------------------------------------------------- */
// // function play(row: number, col: number) {
// //     ticTacToeStore.update(curr => {
// //         if (curr.win) { return curr }
// //         if (curr.board[row][col]) { return curr }
// //         if (row < 0 || row >= curr.board.length) { return curr }
// //         if (col < 0 || col >= curr.board[0].length) { return curr }

// //         let newState = deepcopy(curr)
// //         newState.board[row][col] = curr.currentPlayer
// //         newState.currentPlayer = otherPlayer(curr.currentPlayer)

// //         const winDirection = checkWin(curr.board, curr.currentPlayer, row, col)
// //         if (winDirection) {
// //             newState.win = {
// //                 direction: winDirection,
// //                 winningRow: row,
// //                 winningCol: col
// //             }
// //         }

// //         console.log(newState)
// //         console.log(decode(encode(newState)))
// //         console.log(encode(newState))

// //         return newState
// //     })
// // }


// // /* ----------------------------------------------- CHECK WIN ---------------------------------------------- */
// // function checkWin(board: Board, player: Player, row: number, col: number): WinDirection | null {
// //     // either one on each side, or two to one side
// //     const neighbours = [[0, 1], [1, 0], [1, -1], [1, 1]] // plus their reverse

// //     const blockAt = (row: number, col: number): (Player | null) => {
// //         if (board[row]) {
// //             return board[row][col]
// //         }
// //         return null
// //     }
    
// //     for (const [idx, [addY, addX]] of neighbours.entries()) {
// //         const direction: WinDirection = idx+1

// //         if (blockAt(row + addY, col + addX) === player) {
// //             // two in the original direction
// //             if (blockAt(row + 2*addY, col + 2*addX) === player) { return direction }
// //             // one on either side of the newest block
// //             if (blockAt(row - addY, col - addX) === player) { return direction }
// //         } else if (blockAt(row - addY, col - addX) === player) {
// //             // two in the opposite direction
// //             if (blockAt(row - 2*addY, col - 2*addX) === player) { return direction }
// //         }
// //     }

// //     return null
// // }


// // export type { TicTacToeState, WinInfo }
// // export { gameState, play, Player, WinDirection, winDirectionClass }