<script lang="ts">
import TicTacToeBoard from '$lib/views/TicTacToeBoard.svelte'
import Button from '$lib/views/Button.svelte'

import { writable, derived } from 'svelte/store'

let aiOpponent: boolean = true
let playing: boolean = false

function playAgainstAI() {
    aiOpponent = true
    playing = true
}

function playAgainstHuman() {
    aiOpponent = false
    playing = true
}

function stopGame() {
    playing = false
}

const difficultyStore = writable<0 | 1 | 2>(0)
const difficulty = derived(difficultyStore, s => s)

const onDifficultyChange: svelte.JSX.ChangeEventHandler<HTMLSelectElement> = e => {
    let difficulty: 0 | 1 | 2 = 0
    switch((e.target as HTMLSelectElement).value) {
        case 'hard': difficulty = 1; break
        case 'impossible': difficulty = 2; break
        default: difficulty = 0; break
    }

    difficultyStore.set(difficulty)
}
</script>


<style>
.container {
    display: grid;
    place-items: center;
    padding-top: 100px;
}

.menu {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    place-items: center;
}

.menu :is(h1, h4) {
    grid-column: 1 / span 2;
    text-align: center;
}

#closeButton {
    position: fixed;
    right: 10px;
    top: 10px;
}

h4 {
    font-family: 'Recursive';
}

.row {
    display: flex;
    flex-direction: row;
    align-items: baseline;
}

#difficultyRow {
    margin-top: 30px;
}
#difficulty {
    margin-left: 10px;
    font-family: 'Recursive';
    font-size: 1rem;
}
</style>


<div class="container">
    {#if playing}
        <div id="closeButton">
            <Button click={stopGame}>Close ❌</Button>
        </div>
        <TicTacToeBoard {aiOpponent} {difficulty} />
        {#if aiOpponent}
            <div class="row" id="difficultyRow">
                <label for="difficulty">Difficulty:</label>
                <!-- svelte-ignore a11y-no-onchange -->
                <select on:change={onDifficultyChange} name="difficulty" id="difficulty">
                    <option value="easy">Easy</option>
                    <option value="hard">Hard</option>
                    <option value="impossible">Impossible</option>
                </select>
            </div>
        {/if}
    {:else}
        <div class="menu">
            <h1>Tic Tac Toe</h1>
            <h4>Select an opponent:</h4>
            <Button click={playAgainstAI}>🤖 Computer</Button>
            <Button click={playAgainstHuman}>🙋‍♂️ Friend</Button>
        </div>
    {/if}
</div>
