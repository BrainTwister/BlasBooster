#!groovy

pipeline {

  agent {
    label 'docker'
  }

  options {
    timeout(time: 1, unit: 'HOURS')
  }

  stages {
    stage('Build') {
      parallel {
        stage('gcc-8') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-18.04-gcc-8'
            }
          }
          steps {
            sh './build.sh gcc-8'
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: gcc(id: 'gcc-8', pattern: 'build-gcc-8/make.out')
            }
          }
        }
        stage('clang-9') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-18.04-clang-9'
            }
          }
          steps {
            sh './build.sh clang-9'
          }
          post {
            always {
              recordIssues enabledForFailure: true, aggregatingResults: false,
                tool: gcc(id: 'clang-9', pattern: 'build-clang-9/make.out')
            }
          }
        }
      }
    }
    stage('Test') {
      parallel {
        stage('gcc-8') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-18.04-gcc-8'
            }
          }
          steps {
            sh 'cd build-gcc-8 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitBuilder',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-gcc-8/Testing/*.xml']]
              ])
            }
          }
        }
        stage('clang-9') {
          agent {
            docker {
              reuseNode true
              image 'braintwister/ubuntu-18.04-clang-9'
            }
          }
          steps {
            sh 'cd build-clang-9 && make test'
          }
          post {
            always {
              step([
                $class: 'XUnitBuilder',
                thresholds: [[$class: 'FailedThreshold', unstableThreshold: '1']],
                tools: [[$class: 'GoogleTestType', pattern: 'build-clang-9/Testing/*.xml']]
              ])
            }
          }
        }
      }
    }
    stage('Deploy') {
      agent {
        docker {
          reuseNode true
          image 'braintwister/ubuntu-18.04-gcc-8'
        }
      }
      steps {
        sh 'cd build-gcc-8 && make package'
      }
      post {
        success {
          archiveArtifacts artifacts: "build*/BlasBooster*", fingerprint: true
        }
      }
    }
  }
  post {
    success {
      mail to: 'bernd.doser@braintwister.eu', subject: "SUCCESS: ${currentBuild.fullDisplayName}", body: "Success: ${env.BUILD_URL}"
    }
    failure {
      mail to: 'bernd.doser@braintwister.eu', subject: "FAILURE: ${currentBuild.fullDisplayName}", body: "Failure: ${env.BUILD_URL}"
    }
  }
}
