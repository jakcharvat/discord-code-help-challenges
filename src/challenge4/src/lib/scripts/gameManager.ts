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

type Coordinate = {
    row: number,
    col: number,
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

    private getBestMove(): Coordinate {
        const coord = this.managerInstance._getBestPlay()
        return {
            row: Math.floor(coord / 10),
            col: coord % 10
        }
    }

    private play(row: number, col: number): boolean {
        let playerChanged = false
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

            if (currState.currentPlayer !== copy.currentPlayer) {
                playerChanged = true
            }

            return copy
        })

        return playerChanged
    }

    playPlayer(row: number, col: number) {
        const played = this.play(row, col)
        if (played) { this.playAI() }
    }

    playAI() {
        const coord = this.getBestMove()
        this.play(coord.row, coord.col)
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
