import { derived, Readable, Writable, writable } from 'svelte/store'
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
    win: (WinInfo | null),
    aiPlays: boolean,
    isTie: boolean,
    difficulty: 0 | 1 | 2
}

type Coordinate = {
    row: number,
    col: number,
}

function initialState({ aiPlays }: { aiPlays: boolean }): TicTacToeState {
    return {
        currentPlayer: Player.Cross,
        board: [
            [ 0, 0, 0 ],
            [ 0, 0, 0 ],
            [ 0, 0, 0 ]
        ],
        win: null,
        aiPlays: aiPlays,
        isTie: false,
        difficulty: 0
    }
}

function deepcopy(state: TicTacToeState): TicTacToeState {
    return {
        currentPlayer: state.currentPlayer,
        board: state.board.map(row => Object.assign([], row)),
        win: state.win ? Object.assign({}, state.win) : null,
        aiPlays: state.aiPlays,
        isTie: state.isTie,
        difficulty: state.difficulty
    }
}


/* --------------------------------------------- GAME MANAGER --------------------------------------------- */
class GameManager {
    private managerInstance: any 
    private ticTacToeStore: Writable<TicTacToeState>
    gameState: Readable<TicTacToeState>
    aiPlays: boolean
    difficulty: 0 | 1 | 2

    private constructor(module: any, aiPlays: boolean) {
        this.managerInstance = module
        this.ticTacToeStore = writable(deepcopy(initialState({ aiPlays })))
        this.gameState = derived(this.ticTacToeStore, state => state)
        this.aiPlays = aiPlays

        this.gameState.subscribe(state => {
            this.aiPlays = state.aiPlays
            this.difficulty = state.difficulty
        })
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
        const coord = this.managerInstance._getBestPlay(this.difficulty)
        return {
            row: Math.floor(coord / 10),
            col: coord % 10
        }
    }

    private getIsTie(): boolean {
        return this.managerInstance._getIsTie()
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

            copy.isTie = this.getIsTie()

            return copy
        })

        return playerChanged
    }

    private playAI() {
        const coord = this.getBestMove()
        this.play(coord.row, coord.col)
    }

    playPlayer(row: number, col: number) {
        const played = this.play(row, col)
        if (played && this.aiPlays) { setTimeout(() => {
            this.playAI()
        }, 100) }
    }

    private _reset() {
        this.managerInstance._reset()
    }
    
    reset() {
        this._reset()
        this.ticTacToeStore.update(state => {
            const copy = deepcopy(state)
            copy.board.map(row => row.fill(0))
            copy.isTie = false
            copy.win = null
            copy.currentPlayer = Player.Cross
            return copy
        })
    }

    setDifficulty(newDifficulty: 0 | 1 | 2) {
        this.ticTacToeStore.update(state => {
            if (state.difficulty !== newDifficulty) {
                this._reset()
                const newState = initialState({ aiPlays: state.aiPlays })
                newState.difficulty = newDifficulty
                return newState
            }

            return state
        })
    }

    static async create(aiPlays: boolean): Promise<GameManager> {
        // try {
            const wasm = await GameManager.loadWasm()
            return new GameManager(wasm, aiPlays)
        // } catch(e) {
        //     console.error('Could not instantiate GameManager WASM Module:')
        //     console.error(e)
        // }
    }
}


export default GameManager
export type { WinInfo, TicTacToeState }
export { WinDirection, winDirectionClass, Player }
