<script lang="ts">
import TicTacToeBox from '$lib/views/TicTacToeBox.svelte'
</script>


<style>
#grid {
    display: grid;
    grid-template-columns: repeat(3, max-content);
    gap: 8px;
}
</style>


<div id="grid">
    {#each [0, 1, 2] as row}
        {#each [0, 1, 2] as col}
            <TicTacToeBox row={row} col={col} />
        {/each}
    {/each}
</div>
