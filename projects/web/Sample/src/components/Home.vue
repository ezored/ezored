<template>
  <div>
    <nav
      class="navbar is-light is-fixed-top"
      role="navigation"
      aria-label="main navigation"
    >
      <div class="navbar-brand">
        <router-link :to="{ name: 'Home' }" class="navbar-item">
          <img
            src="../assets/images/logo.png"
            alt="Logo"
            style="max-width: 50px"
          />
          My App
        </router-link>
      </div>
    </nav>

    <section class="section" style="text-align: center; margin-top: 50px">
      <div class="container">
        <h1 class="title">My App</h1>

        <div class="columns is-mobile is-centered">
          <div class="column is-full">
            <img
              alt="Logo"
              src="../assets/images/logo.png"
              style="width: 100px"
            />
          </div>
        </div>

        <div class="columns">
          <div class="column">
            <button class="button is-primary" v-on:click="showCurrentTime()">
              Show current time
            </button>
          </div>
          <div class="column">
            <button class="button is-info" v-on:click="selectFolder()">
              Select folder
            </button>
          </div>
          <div class="column">
            <button class="button is-info" v-on:click="toggleFullscreen()">
              Toggle fullscreen
            </button>
          </div>
          <div class="column">
            <button class="button is-info" v-on:click="openURL()">
              Open URL
            </button>
          </div>
          <div class="column">
            <router-link
              :to="{ name: 'About' }"
              tag="button"
              class="button is-warning"
            >
              About
            </router-link>
          </div>
        </div>

        <div
          v-if="message"
          class="columns is-mobile is-centered"
          style="margin-top: 30px; margin-bottom: 30px"
        >
          <div class="column is-full">
            <article class="message is-info">
              <div class="message-body">
                {{ message }}
              </div>
            </article>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
/* globals pywebview */
export default {
  name: "Home",
  props: {},
  data() {
    return {
      message: "",
    };
  },
  created: function () {
    // ignore
  },
  methods: {
    showCurrentTime() {
      pywebview.api
        .call("modules.datetime.get_now", { timestamp: new Date().getTime() })
        .then((result) => {
          this.message = result;
        })
        .catch((e) => {
          this.message = "Error: " + e;
        });
    },

    toggleFullscreen() {
      pywebview.api
        .call("modules.system.toggle_fullscreen")
        .then((result) => {
          this.message = result;
        })
        .catch((e) => {
          this.message = "Error: " + e;
        });

      pywebview.api.toggleFullscreen().then((result) => {
        this.message = result;
      });
    },

    selectFolder() {
      this.message = "Loading...";

      pywebview.api
        .call("modules.system.select_folder")
        .then((result) => {
          this.message = result;
        })
        .catch((e) => {
          this.message = "Error: " + e;
        });
    },

    openURL() {
      this.message = "Loading...";

      pywebview.api
        .call("modules.net.open_url", { url: "https://httpbin.org/get" })
        .then((result) => {
          this.message = result;
        })
        .catch((e) => {
          this.message = "Error: " + e;
        });
    },
  },
};
</script>

<style scoped>
</style>
