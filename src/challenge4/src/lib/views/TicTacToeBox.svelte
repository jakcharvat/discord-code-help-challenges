<script lang="ts">
import type GameManager from "$lib/scripts/gameManager"
import { Player } from "$lib/scripts/gameManager"
import { getContext, onMount } from "svelte"


export let row: number
export let col: number

let className = ''

let gameManager: GameManager | null

function click() {
    gameManager.playPlayer(row, col)
}

const { getGameManager } = getContext('gameManager')

onMount(() => {
    gameManager = getGameManager()
    gameManager.gameState.subscribe(state => {
        const player = state.board[row][col]
        if (!player) {
            if (state.win) { className = 'won'; return }
            className = state.currentPlayer === Player.Cross ? 'possible-cross' : 'possible-naught'
        } else { 
            className = player === Player.Cross ? 'cross' : 'naught'
        }
    })
})
</script>


<style>
button {
    --primary-colour: #68dba3;
    --background-colour: var(--primary-colour);
    --size: var(--box-size);

    --shadow-offset: 6px;
    --shadow-colour: #3faf79;
    --hover-translate: calc(-1 * var(--shadow-offset) / 2);

    --cross-colour: #1e6b46;

    background: var(--background-colour);
    width: var(--size);
    height: var(--size);
    outline: none;
    border: none;
}

button:not(:is(.cross, .naught, .won)):hover {
    box-shadow: var(--shadow-offset) var(--shadow-offset) 0 0 var(--shadow-colour);
    transform: translate(var(--hover-translate), var(--hover-translate));
    cursor: pointer;
}


button:is(.cross, .possible-cross, .naught, .possible-naught)::before, 
button:is(.cross, .possible-cross)::after {
    --translate: translate(-50%, -50%);
    content: '';
    position: absolute;
    transform: var(--translate) var(--rotate);
}

button:is(.cross, .possible-cross)::before, 
button:is(.cross, .possible-cross)::after {
    width: 100px;
    height: 20px;
    background: var(--cross-colour);
}

button:is(.cross, .possible-cross)::before {
    --rotate: rotate(-45deg);
}

button:is(.cross, .possible-cross)::after {
    --rotate: rotate(45deg);
}

button:is(.possible-cross, .possible-naught)::before,
button:is(.possible-cross, .possible-naught)::after {
    opacity: 0;
}

button:is(.possible-cross, .possible-naught):hover::before,
button:is(.possible-cross, .possible-naught):hover::after {
    opacity: 0.2;
}


button:is(.naught, .possible-naught)::before {
    --size: 46px;
    --rotate: rotate(0deg);
    width: var(--size);
    height: var(--size);
    border: 20px solid var(--cross-colour);
    border-radius: 100%;
}



button.no-manager {
    background: salmon;
}
</style>

{#if gameManager}
    <button class={className} on:click={() => click()}></button>
{:else}
    <button class="no-manager">MISSING GAME MANAGER</button>
{/if}
