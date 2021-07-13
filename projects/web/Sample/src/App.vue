<template>
  <router-view />
</template>

<script>
/* globals pywebview */
window.addEventListener("pywebviewready", function () {
  pywebview.api
    .call("modules.app.initialize")
    .then(() => {
      console.log("PyWebview is ready!");
    })
    .catch((e) => {
      console.log("PyWebview error: " + e);
    });
});

export default {
  name: "App",
  components: {},
};
</script>

<style>
</style>
