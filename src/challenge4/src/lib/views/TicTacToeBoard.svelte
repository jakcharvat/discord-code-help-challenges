<script lang="ts">
import type { TicTacToeState, WinInfo } from '$lib/scripts/gameManager'
import GameManager, { Player, winDirectionClass } from '$lib/scripts/gameManager';
import TicTacToeBox from '$lib/views/TicTacToeBox.svelte'
import Button from '$lib/views/Button.svelte'
import { onMount, setContext } from 'svelte'
import type { Readable } from 'svelte/store';

const getWinClass = (win: WinInfo): string => {
    const direction = winDirectionClass(win.direction)
    const row = `win-row-${win.winningRow}`
    const col = `win-col-${win.winningCol}`
    return `win ${direction} ${row} ${col}`
}

export let aiOpponent: boolean
export let difficulty: Readable<0 | 1 | 2>

let winClass: string = ''
let managerInstance: GameManager | null

difficulty.subscribe(changeDifficulty)

setContext('gameManager', {
    getGameManager: (): GameManager => managerInstance
})

let titleText: string = ''
let isGameOver: boolean = false

function changeDifficulty(newDiff: 0 | 1 | 2) {
    managerInstance?.setDifficulty(newDiff)
}

function playerCharacter(player: Player): string {
    switch (player) {
        case Player.Cross: return '❌'
        case Player.Naught: return '⭕️'
    }
}

function getTitleText(state: TicTacToeState): string {
    if (state.isTie) {
        return `It's a tie! 👔`
    }

    if (aiOpponent) {
        if (state.win) {
            if (state.currentPlayer === Player.Cross) {
                return 'Congrats! You won! 🎉'
            }
            return 'You lost 😞'
        }

        if (state.currentPlayer === Player.Cross) {
            return 'Your turn...'
        }
        return '🤖 playing...'
    }
    if (state.win) {
        return `${playerCharacter(state.currentPlayer)} won! 🎉`
    }
    return `${playerCharacter(state.currentPlayer)}'s turn`
}

async function newGame() {
    managerInstance.reset()
}

export { changeDifficulty }

onMount(async () => {
    managerInstance = await GameManager.create(aiOpponent)
    managerInstance.gameState.subscribe(state => {
        const win = state.win
        if (win) {
            winClass = getWinClass(win)
        } else {
            winClass = ''
        }

        titleText = getTitleText(state)

        isGameOver = state.isTie || (!!state.win)
    })
})
</script>


<style>
#grid {
    --grid-gap: 8px;
    --box-size: 100px;

    --win-line-length: 300px;
    --win-line-breadth: 20px;
    --win-line-background: #13271e;

    --center-in-box: calc(var(--box-size) / 2);
    --skip-box: calc(var(--box-size) + var(--grid-gap));

    display: grid;
    grid-template-columns: repeat(3, max-content);
    gap: var(--grid-gap);
    position: relative;
}

#grid.win::before { 
    --rotate: 0deg;
    content: '';
    background: var(--win-line-background);
    position: absolute;
    z-index: 10;
    transform: translate(-50%, -50%) rotate(var(--rotate));
    width: var(--win-line-length);
    height: var(--win-line-breadth);
}

#grid.win-horizontal::before {
    left: 50%;
}

#grid.win-horizontal.win-row-0::before {
    top: var(--center-in-box);
}
#grid.win-horizontal.win-row-1::before {
    top: calc(var(--skip-box) + var(--center-in-box));
}
#grid.win-horizontal.win-row-2::before {
    top: calc(var(--skip-box)*2 + var(--center-in-box));
}


#grid.win-vertical::before {
    --rotate: 90deg;
    top: 50%;
}

#grid.win-vertical.win-col-0::before {
    left: var(--center-in-box);
}
#grid.win-vertical.win-col-1::before {
    left: calc(var(--skip-box) + var(--center-in-box));
}
#grid.win-vertical.win-col-2::before {
    left: calc(var(--skip-box)*2 + var(--center-in-box));
}


#grid.win-diagonal::before {
    --win-line-length: 360px;
    --win-line-breadth: 15px;
    left: 50%;
    top: 50%;
}

#grid.win-diagonal-forward::before {
    --rotate: -45deg;
}

#grid.win-diagonal-back::before {
    --rotate: 45deg;
}

#newGameButton {
    margin-top: 20px;
}
</style>


{#if managerInstance}
    <h1>{titleText}</h1>
    <div id="grid" class={winClass}>
        {#each [0, 1, 2] as row}
            {#each [0, 1, 2] as col}
                <TicTacToeBox row={row} col={col} />
            {/each}
        {/each}
    </div>
    {#if isGameOver}
        <div id="newGameButton">
            <Button click={newGame}>New Game</Button>
        </div>
    {/if}
{:else}
    <h3>Loading TicTacToe...</h3>
{/if}
