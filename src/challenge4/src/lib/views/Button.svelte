<script lang="ts">
export let click: svelte.JSX.MouseEventHandler<HTMLButtonElement>
export let className: string = ''
</script>


<style>
button {
    --background-colour: var(--primary-colour);
    --size: var(--box-size);

    --shadow-offset: 6px;
    --hover-translate: calc(-1 * var(--shadow-offset) / 2);

    font-family: 'Recursive', sans-serif;
    font-size: 1rem;
    font-weight: 300;
    font-variation-settings: 'CASL' 0;
    transition: font-weight             150ms ease,
                font-variation-settings 150ms ease,
                background              150ms ease;
    padding: 10px;
    background: var(--primary-colour);
    color: var(--foreground-colour);
    border: solid 2px var(--foreground-colour);
    cursor: pointer;
}

button:hover {
    font-weight: 850;
    font-variation-settings: 'CASL' 0.8;
    box-shadow: var(--shadow-offset) var(--shadow-offset) 0 0 var(--shadow-colour);
    transform: translate(var(--hover-translate), var(--hover-translate));
    cursor: pointer;
}
</style>


<button class={className} on:click={click}>
    <slot />
</button>