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
            style="max-width: 50px; margin-right: 10px"
          />
          Ezored
        </router-link>
      </div>
    </nav>

    <section class="section" style="text-align: center; margin-top: 50px">
      <div class="container">
        <h1 class="title">ToDo List</h1>

        <div class="columns">
          <div class="column">
            <!-- LOADING -->
            <div v-if="isLoading" class="box">
              <strong>Loading...</strong>
            </div>

            <!-- LIST -->
            <div v-if="!isLoading" class="list is-hoverable">
              <div v-for="item in listData" :key="item.id">
                <!-- CARD -->
                <div class="card">
                  <div class="card-content">
                    <div class="media">
                      <div class="media-left">
                        <div class="control">
                          <label class="checkbox">
                            <input
                              type="checkbox"
                              v-model="item.done"
                              @click="setItemAsDone(item)"
                            />
                          </label>
                        </div>
                      </div>
                      <div class="media-content">
                        <p class="title is-4 has-text-left">
                          {{ item.title }}
                        </p>
                      </div>
                    </div>
                    <div class="content has-text-left">
                      {{ item.body }}
                      <br />
                      <br />
                      <small>
                        Created at:
                        {{ $moment(item.createdAt).local().format("L LTS") }}
                      </small>
                      <br />
                      <small>
                        Updated at:
                        {{ $moment(item.updatedAt).local().format("L LTS") }}
                      </small>
                    </div>
                  </div>
                </div>
                <br />
              </div>
            </div>

            <button class="button is-primary" v-on:click="back()">Back</button>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>

<script>
import { util } from "@/mixins/util";

export default {
  name: "ToDo",
  mixins: [util],
  props: {},
  data() {
    return {
      isLoading: false,
      listData: [],
    };
  },
  created: function () {
    this.loadList();
  },
  methods: {
    async loadList() {
      this.isLoading = true;

      var url = "http://localhost:9090/todo/list";

      await this.sleep(1000);

      this.$http
        .get(url)
        .then((response) => {
          var r = response.data;

          if (r.success) {
            this.listData = r.data.list;
            this.isLoading = false;
          } else {
            this.isLoading = false;
          }
        })
        .catch(() => {
          this.isLoading = false;
        });
    },

    sleep(ms) {
      return new Promise((resolve) => {
        setTimeout(resolve, ms);
      });
    },

    setItemAsDone(todoItem) {
      var url = "http://localhost:9090/todo/done-by-id";

      var data = JSON.stringify({
        id: todoItem.id,
        done: !todoItem.done,
      });

      var headers = {
        "Content-Type": "application/json",
      };

      this.$http
        .post(url, data, { headers: headers })
        .then((response) => {
          var r = response.data;

          if (r.success) {
            for (var x = 0; x < this.listData.length; x++) {
              var item = this.listData[x];

              if (item.id == todoItem.id) {
                var todo = this.listData[x];

                todo.done = r.data.todo.done;
                todo.updatedAt = r.data.todo.updatedAt;

                this.listData[x] = todo;

                break;
              }
            }
          } else {
            // ignore
          }
        })
        .catch(() => {
          // ignore
        });
    },

    back() {
      this.$router.push({ name: "Home", params: {} });
    },
  },
};
</script>

<style scoped>
</style>
